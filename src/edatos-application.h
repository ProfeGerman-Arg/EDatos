#include <gtk/gtk.h>
#pragma once


G_BEGIN_DECLS

#define EDATOS_TYPE_APPLICATION (edatos_application_get_type())

G_DECLARE_FINAL_TYPE (EdatosApplication, edatos_application, EDATOS, APPLICATION, GtkApplication)

EdatosApplication *edatos_application_new (void);

G_END_DECLS
