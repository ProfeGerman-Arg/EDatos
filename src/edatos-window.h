
#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define EDATOS_TYPE_WINDOW (edatos_window_get_type())

G_DECLARE_FINAL_TYPE (EdatosWindow, edatos_window, EDATOS, WINDOW, GtkApplicationWindow)

G_END_DECLS
