#include <gtk/gtk.h>
#include "objeto.hpp"
#include "ponto.hpp"
#include "reta.hpp"
#include "poligono.hpp"

int main (int argc, char *argv[]) {
  GtkBuilder *builder;
  GtkWidget *mainWindow;

  gtk_init(&argc, &argv);

  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "src/ui.glade", nullptr);

  mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
  g_signal_connect(mainWindow, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

  gtk_widget_show(mainWindow);

  gtk_main();

  return 0;
}
