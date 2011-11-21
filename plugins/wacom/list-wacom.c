/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * Author: Bastien Nocera <hadess@hadess.net>
 *
 */

#include "config.h"

#include <gtk/gtk.h>

#include "gsd-wacom-device.h"

static char *
get_loc (GSettings *settings)
{
	char *path, *schema, *ret;

	g_return_val_if_fail (G_IS_SETTINGS (settings), NULL);

	g_object_get (G_OBJECT (settings),
		      "path", &path,
		      "schema", &schema,
		      NULL);
	ret = g_strdup_printf ("schema: %s (path: %s)", schema, path);
	g_free (schema);
	g_free (path);

	return ret;
}

#define BOOL_AS_STR(x) (x ? "yes" : "no")

int main (int argc, char **argv)
{
	GdkDeviceManager *mgr;
	GList *list, *l;

	gtk_init (&argc, &argv);

	mgr = gdk_display_get_device_manager (gdk_display_get_default ());

	list = gdk_device_manager_list_devices (mgr, GDK_DEVICE_TYPE_SLAVE);
	for (l = list; l ; l = l->next) {
		GsdWacomDevice *device;
		char *loc;

		device = gsd_wacom_device_new (l->data);
		if (gsd_wacom_device_get_device_type (device) == WACOM_TYPE_INVALID) {
			g_object_unref (device);
			continue;
		}
		g_message ("*** Device '%s' (type: %s)",
			   gsd_wacom_device_get_name (device),
			   gsd_wacom_device_type_to_string (gsd_wacom_device_get_device_type (device)));
		g_message ("\tReversible: %s", BOOL_AS_STR (gsd_wacom_device_reversible (device)));
		g_message ("\tScreen Tablet: %s", BOOL_AS_STR (gsd_wacom_device_is_screen_tablet (device)));

		loc = get_loc (gsd_wacom_device_get_settings (device));
		g_message ("\tGeneric settings: %s", loc);
		g_free (loc);

		if (gsd_wacom_device_get_device_type (device) != WACOM_TYPE_STYLUS) {
			loc = get_loc (gsd_wacom_device_get_tool_settings (device));
			g_message ("\tTool settings: %s", loc);
			g_free (loc);
		}

		if (gsd_wacom_device_get_device_type (device) == WACOM_TYPE_STYLUS) {
			GList *styli, *j;

			styli = gsd_wacom_device_list_styli (device);
			for (j = styli; j; j = j->next) {
				GsdWacomStylus *stylus;
				char *loc;

				stylus = j->data;
				g_message ("\tStylus: '%s'", gsd_wacom_stylus_get_name (stylus));

				loc = get_loc (gsd_wacom_stylus_get_settings (stylus));
				g_message ("\t\tSettings: %s", loc);
				g_free (loc);
			}
			g_list_free (styli);
		}
		g_object_unref (device);
	}
	g_list_free (list);

	return 0;
}
