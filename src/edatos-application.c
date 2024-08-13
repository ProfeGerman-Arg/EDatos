#include <glib/gi18n.h>
#include "edatos-application.h"
#include "edatos-window.h"

struct _EdatosApplication
{
  GtkApplication parent_instance;
  GtkWindow *window;
};

G_DEFINE_TYPE (EdatosApplication, edatos_application, GTK_TYPE_APPLICATION)

static void
edatos_application_quit_action (GSimpleAction *action,
                                     GVariant      *parameter,
                                     gpointer      *user_data)
{
 EdatosApplication *edatos;
 edatos = EDATOS_APPLICATION (user_data);
 gtk_widget_destroy (GTK_WIDGET (edatos -> window));
}

static void
edatos_application_activate (GtkApplication *application)
{
  EdatosApplication *edatos;
  g_assert (GTK_IS_APPLICATION (application));
  edatos = EDATOS_APPLICATION (application);
  edatos -> window = gtk_application_get_active_window (application);
  if (edatos -> window == NULL)
    edatos -> window = g_object_new (EDATOS_TYPE_WINDOW,
                                 "application",application,
                                 NULL);
  gtk_window_present (edatos -> window);

}

static void
edatos_application_startup (GtkApplication *application)
{
  EdatosApplication *edatos;
  edatos = EDATOS_APPLICATION (application);
  static const GActionEntry app_entry[] = {
      {"quit", edatos_application_quit_action, NULL, NULL, NULL}
      //{"about_dialog", proyectogui_application_about_action, NULL, NULL, NULL},
  };
  g_action_map_add_action_entries (G_ACTION_MAP (application),
                                   app_entry,
                                   G_N_ELEMENTS (app_entry),
                                   application);
  G_APPLICATION_CLASS (edatos_application_parent_class) -> startup (application);
}

EdatosApplication *
edatos_application_new (void)
{
  return g_object_new (EDATOS_TYPE_APPLICATION,
                       "resource_base_path", "Proyectos/Builder/EDatos",
                       "application-id", "/org/profe/EDatos",
                       "flags", G_APPLICATION_HANDLES_OPEN,
                       NULL);
}


static void
edatos_application_class_init (EdatosApplicationClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  G_APPLICATION_CLASS (klass) ->activate = edatos_application_activate;
  G_APPLICATION_CLASS (klass) ->startup = edatos_application_startup;

}

static void
edatos_application_init (EdatosApplication *self)
{
  gtk_application_set_accels_for_action (GTK_APPLICATION (self),
                                         "win.limpiar",
                                         (const char *[]) { NULL, NULL});
  gtk_application_set_accels_for_action (GTK_APPLICATION (self),
                                         "win.cargar",
                                         (const char *[]) { NULL, NULL});
}
