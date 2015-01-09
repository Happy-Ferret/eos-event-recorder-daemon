/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */

#include "metrics-util.h"

/* For clock_gettime() */
#if !defined(_POSIX_C_SOURCE) || _POSIX_C_SOURCE < 199309L
#error "This code requires _POSIX_C_SOURCE to be 199309L or later."
#endif

#include <errno.h>
#include <time.h>
#include <inttypes.h>

#include <glib.h>
#include <gio/gio.h>
#include <uuid/uuid.h>

static void
trash_event_value (EventValue *event_value)
{
  GVariant *auxiliary_payload = event_value->auxiliary_payload;
  if (auxiliary_payload != NULL)
    g_variant_unref (auxiliary_payload);
}

void
trash_singular_event (SingularEvent *singular)
{
  EventValue *event_value = &singular->event_value;
  trash_event_value (event_value);
}

void
trash_aggregate_event (AggregateEvent *aggregate)
{
  SingularEvent *event = &aggregate->event;
  trash_singular_event (event);
}

void
trash_sequence_event (SequenceEvent *sequence)
{
  for (gint i = 0; i < sequence->num_event_values; ++i)
    trash_event_value (sequence->event_values + i);

  g_free (sequence->event_values);
}

void
free_singular_buffer (SingularEvent *singular_buffer,
                      gint           num_singulars_buffered)
{
  for (gint i = 0; i < num_singulars_buffered; i++)
    trash_singular_event (singular_buffer + i);

  g_free (singular_buffer);
}

void
free_aggregate_buffer (AggregateEvent *aggregate_buffer,
                       gint            num_aggregates_buffered)
{
  for (gint i = 0; i < num_aggregates_buffered; i++)
    trash_aggregate_event (aggregate_buffer + i);

  g_free (aggregate_buffer);
}

void
free_sequence_buffer (SequenceEvent *sequence_buffer,
                      gint           num_sequences_buffered)
{
  for (gint i = 0; i < num_sequences_buffered; i++)
    trash_sequence_event (sequence_buffer + i);

  g_free (sequence_buffer);
}

void
free_variant_array (GVariant **variant_array)
{
  for (gint i = 0; variant_array[i] != NULL; i++)
    g_variant_unref (variant_array[i]);

  g_free (variant_array);
}

GVariant *
singular_to_variant (SingularEvent *singular)
{
  GVariantBuilder event_id_builder;
  get_uuid_builder (singular->event_id, &event_id_builder);
  EventValue event_value = singular->event_value;
  return g_variant_new ("(uayxmv)", singular->user_id, &event_id_builder,
                        event_value.relative_timestamp,
                        event_value.auxiliary_payload);
}

GVariant *
aggregate_to_variant (AggregateEvent *aggregate)
{
  SingularEvent event = aggregate->event;
  GVariantBuilder event_id_builder;
  get_uuid_builder (event.event_id, &event_id_builder);
  EventValue event_value = event.event_value;
  return g_variant_new ("(uayxxmv)", event.user_id, &event_id_builder,
                        event_value.relative_timestamp, aggregate->num_events,
                        event_value.auxiliary_payload);
}

GVariant *
sequence_to_variant (SequenceEvent *sequence)
{
  GVariantBuilder event_values_builder;
  g_variant_builder_init (&event_values_builder, G_VARIANT_TYPE ("a(xmv)"));
  for (gint i = 0; i < sequence->num_event_values; i++)
    {
      EventValue event_value = sequence->event_values[i];
      g_variant_builder_add (&event_values_builder, "(xmv)",
                             event_value.relative_timestamp,
                             event_value.auxiliary_payload);
    }

  GVariantBuilder event_id_builder;
  get_uuid_builder (sequence->event_id, &event_id_builder);

  return g_variant_new ("(uaya(xmv))", sequence->user_id, &event_id_builder,
                        &event_values_builder);

}

/*
 * Returns a new reference to a little-endian version of GVariant * regardless
 * of this machine's endianness. Crashes with a g_error if this machine is
 * middle-endian (a.k.a., mixed-endian).
 *
 * The returned GVariant * should have g_variant_unref() called on it when it is
 * no longer needed.
 */
GVariant *
swap_bytes_if_big_endian (GVariant *variant)
{
  if (G_BYTE_ORDER == G_BIG_ENDIAN)
    return g_variant_byteswap (variant);

  if (G_BYTE_ORDER != G_LITTLE_ENDIAN)
    g_error ("Holy crap! This machine is neither big NOR little-endian, time "
             "to panic. AAHAHAHAHAH!");

  return g_variant_ref_sink (variant);
}

/*
 * Initializes the given uuid_builder and populates it with the contents of
 * uuid.
 */
void
get_uuid_builder (uuid_t           uuid,
                  GVariantBuilder *uuid_builder)
{
  g_variant_builder_init (uuid_builder, G_VARIANT_TYPE ("ay"));
  for (size_t i = 0; i < UUID_LENGTH; ++i)
    g_variant_builder_add (uuid_builder, "y", uuid[i]);
}