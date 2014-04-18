/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */

/* Copyright 2014 Endless Mobile, Inc. */

#ifndef EMTR_EVENT_TYPES_H
#define EMTR_EVENT_TYPES_H

#if !(defined(_EMTR_INSIDE_EOSMETRICS_H) || defined(COMPILING_EOS_METRICS))
#error "Please do not include this header file directly."
#endif

G_BEGIN_DECLS

/**
 * SECTION:emtr-event-types
 * @title: Event Types
 * @short_description: shared constant definitions for event types
 *
 * Event types are RFC 4122 UUIDs. This file provides a mapping from
 * 36-character string representations of UUIDs to human-readable constants. New
 * event types should be registered here. UUIDs should never be recycled since
 * this will create confusion when analyzing the metrics database. The list is
 * sorted alphabetically by name.
 *
 * To generate a new UUID on Endless OS, Debian, or Ubuntu:
 * |[
 * sudo apt-get install uuid-runtime
 * uuidgen -r
 * ]|
 */

/**
 * EMTR_EVENT_USER_LOGGED_IN:
 *
 * Started when a user logs in and stopped when that user logs out.
 */
#define EMTR_EVENT_USER_LOGGED_IN "ab839fd2-a927-456c-8c18-f1136722666b"

/**
 * EMTR_EVENT_NETWORK_STATUS_CHANGED:
 *
 * Recorded when the network changes from one of the states described at
 * https://developer.gnome.org/NetworkManager/unstable/spec.html#type-NM_STATE
 * to another. The auxiliary payload is a 2-tuple of the form
 * (previous_network_state, new_network_state). Since events are delivered on a
 * best-effort basis, there is no guarantee that the new network state of the
 * previous successfully recorded network status change event matches the
 * previous network state of the current network status change event.
 */
#define EMTR_EVENT_NETWORK_STATUS_CHANGED "5fae6179-e108-4962-83be-c909259c0584"

G_END_DECLS

#endif /* EMTR_EVENT_TYPES_H */
