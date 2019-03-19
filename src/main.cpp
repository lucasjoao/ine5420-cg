#include <gtk/gtk.h>
#include "ListaEnc.hpp"

int main (int argc, char *argv[]) {

  GtkWidget *window;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);
  gtk_widget_show(window);
  gtk_widget_set_size_request(window, 800, 600);
  gtk_window_set_title(GTK_WINDOW(window), "INE5420 - João / Lucas");
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

  gtk_main();

  return 0;
}
