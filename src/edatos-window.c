
#include "edatos-config.h"
#include "edatos-window.h"


struct _EdatosWindow
{
  GtkApplicationWindow  parent_instance;

  /* Template widgets */
  GtkHeaderBar        *header_bar;
  GtkBox              *box_gral;
  GtkBox              *box_nombre;
  GtkLabel            *label_nombre;
  GtkEntry            *entry_nombre;
  GtkBox              *box_apellido;
  GtkLabel            *label_apellido;
  GtkEntry            *entry_apellido;
  GtkBox              *box_dni;
  GtkLabel            *label_dni;
  GtkEntry            *entry_dni;
  GtkBox              *box_buttons;
  GtkButton           *button_oka;
  GtkButton           *button_borrar;
  GtkButton           *button_salir;
  GtkBox              *box_datos;
  GtkSeparator        *separator_datos;
  GtkLabel            *label_datos;
  GtkTreeView         *treeview_datos;
  GtkListStore        *liststore_datos;

};

G_DEFINE_TYPE (EdatosWindow, edatos_window, GTK_TYPE_APPLICATION_WINDOW)

static void
edatos_window_class_init (EdatosWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/profe/EDatos/edatos-window.ui");
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, box_gral);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, box_nombre);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, label_nombre);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, entry_nombre);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, box_apellido);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, label_apellido);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, entry_apellido);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, box_dni);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, label_dni);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, entry_dni);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, box_buttons);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, button_oka);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, button_borrar);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, button_salir);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, box_datos);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, separator_datos);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, label_datos);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, treeview_datos);
  gtk_widget_class_bind_template_child (widget_class, EdatosWindow, liststore_datos);
}

struct TEstDatos{
  char nombre[10];
  char apellido[30];
  int dni;
};

int pos=0;

static void
inicializar_lista (EdatosWindow *self)
{
  GtkCellRenderer *renderer;
  renderer=gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (self->treeview_datos), -1, "Nombre", renderer,"text",0, NULL);
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (self->treeview_datos), -1, "Apellido", renderer,"text",1, NULL);
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (self->treeview_datos), -1, "DNI", renderer,"text",2, NULL);
}

static void
limpiar_datos(EdatosWindow *self)
{
  gtk_entry_set_text (GTK_ENTRY (self->entry_nombre), "");
  gtk_entry_set_text (GTK_ENTRY (self->entry_apellido), "");
  gtk_entry_set_text (GTK_ENTRY (self->entry_dni), "");
  if(pos==3){
    gtk_widget_set_sensitive (GTK_BUTTON (self->button_oka), FALSE);
    gtk_widget_set_sensitive (GTK_BUTTON (self->button_borrar), FALSE);
    gtk_label_set_text (GTK_LABEL (self->label_datos), "ESTRUCTURA COMPLETA");
    };
}

static void
limpiar_clickeado (EdatosWindow *self)
{
  limpiar_datos (self);
}


static void
cargar_clickeado (EdatosWindow *self)
{
  struct  TEstDatos EstDatos[3];
  GtkTreeIter iter;
  if (gtk_entry_get_text_length (GTK_ENTRY(self->entry_nombre)) == 0){
    gtk_label_set_text (GTK_LABEL (self->label_datos), "INGRESE SU NOMBRE");
    gtk_entry_grab_focus_without_selecting (GTK_ENTRY(self->entry_nombre));
  }
  else
    if(gtk_entry_get_text_length (GTK_ENTRY(self->entry_apellido)) == 0){
      gtk_label_set_text (GTK_LABEL (self->label_datos), "INGRESE SU APELLIDO");
      gtk_entry_grab_focus_without_selecting (GTK_ENTRY(self->entry_apellido));
    }
    else
      if(gtk_entry_get_text_length (GTK_ENTRY(self->entry_dni)) == 0){
        gtk_label_set_text (GTK_LABEL (self->label_datos), "INGRESE SU DNI");
        gtk_entry_grab_focus_without_selecting (GTK_ENTRY(self->entry_dni));
      }
      else{
        strcpy(EstDatos[pos].nombre,gtk_entry_get_text (self->entry_nombre));
        strcpy(EstDatos[pos].apellido,gtk_entry_get_text (self->entry_apellido));
        EstDatos[pos].dni=atoi(gtk_entry_get_text (self->entry_dni));
        gtk_label_set_text (GTK_LABEL (self->label_datos), "DATOS CARGADOS");
        gtk_list_store_append (GTK_LIST_STORE (self->liststore_datos), &iter);
        gtk_list_store_set (GTK_LIST_STORE (self->liststore_datos), &iter, 0, EstDatos[pos].nombre,1, EstDatos[pos].apellido,2, EstDatos[pos].dni,-1);
        pos=pos+1;
        limpiar_datos (self);
        gtk_entry_grab_focus_without_selecting (GTK_ENTRY(self->entry_nombre));
      };
}

static void//
capturar_accion (EdatosWindow *self, gchar *action_name, GCallback handler)
{

  GSimpleAction *action = g_simple_action_new (action_name, NULL);
  g_signal_connect_swapped (action, "activate", handler, self);
  g_action_map_add_action (G_ACTION_MAP (self), G_ACTION (action));
}

static void
edatos_window_init (EdatosWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
  inicializar_lista(self);
  capturar_accion (self, "limpiar", G_CALLBACK(limpiar_clickeado));
  capturar_accion (self, "cargar", G_CALLBACK(cargar_clickeado));
}
