/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */

/* Copyright 2014, 2015 Endless Mobile, Inc. */

/*
 * This file is part of eos-event-recorder-daemon.
 *
 * eos-event-recorder-daemon is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or (at your
 * option) any later version.
 *
 * eos-event-recorder-daemon is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with eos-event-recorder-daemon.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "emer-network-send-provider.h"

#include <gio/gio.h>
#include <glib.h>

typedef struct _EmerNetworkSendProviderPrivate
{
  gint send_number;
} EmerNetworkSendProviderPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (EmerNetworkSendProvider, emer_network_send_provider, G_TYPE_OBJECT)

static void
emer_network_send_provider_class_init (EmerNetworkSendProviderClass *klass)
{
}

static void
emer_network_send_provider_init (EmerNetworkSendProvider *self)
{
}


/* MOCK PUBLIC API */

EmerNetworkSendProvider *
emer_network_send_provider_new (const gchar *path)
{
  return g_object_new (EMER_TYPE_NETWORK_SEND_PROVIDER, NULL);
}

gint
emer_network_send_provider_get_send_number (EmerNetworkSendProvider *self)
{
  EmerNetworkSendProviderPrivate *priv =
    emer_network_send_provider_get_instance_private (self);

  return priv->send_number;
}

void
emer_network_send_provider_increment_send_number (EmerNetworkSendProvider *self)
{
  EmerNetworkSendProviderPrivate *priv =
    emer_network_send_provider_get_instance_private (self);

  priv->send_number++;
}
