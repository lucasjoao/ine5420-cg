#include <gtk/gtk.h>
#include "objeto.hpp"
#include "ponto.hpp"
#include "reta.hpp"
#include "poligono.hpp"
#include <iostream>

/* ---------- TELA PRINCIPAL ---------- */

GtkBuilder *builder;
GtkWidget *mainWindow;


/* ---------- BOTOES TELA PRINCIPAL ---------- */
GtkButton* btn_zoom_in;
GtkButton* btn_zoom_out;

GtkButton* btn_up;
GtkButton* btn_down;
GtkButton* btn_left;
GtkButton* btn_right;

GtkButton* btn_ponto;
GtkButton* btn_reta;
GtkButton* btn_poligono;

/* ---------- FUNCOES DOS BOTOES DA TELA PRINCIPAL ---------- */
void btn_zoom_in_clicked(GtkWidget *widget, gpointer data);
void btn_zoom_out_clicked(GtkWidget *widget, gpointer data);

void btn_up_clicked(GtkWidget *widget, gpointer data);
void btn_down_clicked(GtkWidget *widget, gpointer data);
void btn_left_clicked(GtkWidget *widget, gpointer data);
void btn_right_clicked(GtkWidget *widget, gpointer data);

void btn_ponto_clicked(GtkWidget *widget, gpointer data);
void btn_reta_clicked(GtkWidget *widget, gpointer data);
void btn_poligono_clicked(GtkWidget *widget, gpointer data);

/* ---------- ---------- */



int main (int argc, char *argv[]) {

  gtk_init(&argc, &argv);

  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "src/ui.glade", nullptr);

  mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
  g_signal_connect(mainWindow, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

  gtk_widget_show(mainWindow);


/* ---------- BOTOES TELA PRINCIPAL ---------- */

  btn_zoom_in = GTK_BUTTON(gtk_builder_get_object(builder, "btnZoomIn"));
  btn_zoom_out = GTK_BUTTON(gtk_builder_get_object(builder, "btnZoomOut"));
  btn_up = GTK_BUTTON(gtk_builder_get_object(builder, "btnUp"));
  btn_down = GTK_BUTTON(gtk_builder_get_object(builder, "btnDown"));
  btn_left = GTK_BUTTON(gtk_builder_get_object(builder, "btnLeft"));
  btn_right = GTK_BUTTON(gtk_builder_get_object(builder, "btnRight"));
  btn_ponto = GTK_BUTTON(gtk_builder_get_object(builder, "btnPonto"));
  btn_reta = GTK_BUTTON(gtk_builder_get_object(builder, "btnReta"));
  btn_poligono = GTK_BUTTON(gtk_builder_get_object(builder, "btnPoligono"));

  g_signal_connect (btn_zoom_in, "clicked", G_CALLBACK (btn_zoom_in_clicked), NULL);
  g_signal_connect (btn_zoom_out, "clicked", G_CALLBACK (btn_zoom_out_clicked), NULL);
  g_signal_connect (btn_up, "clicked", G_CALLBACK (btn_up_clicked), NULL);
  g_signal_connect (btn_down, "clicked", G_CALLBACK (btn_down_clicked), NULL);
  g_signal_connect (btn_left, "clicked", G_CALLBACK (btn_left_clicked), NULL);
  g_signal_connect (btn_right, "clicked", G_CALLBACK (btn_right_clicked), NULL);
  g_signal_connect (btn_ponto, "clicked", G_CALLBACK (btn_ponto_clicked), NULL);
  g_signal_connect (btn_reta, "clicked", G_CALLBACK (btn_reta_clicked), NULL);
  g_signal_connect (btn_poligono, "clicked", G_CALLBACK (btn_poligono_clicked), NULL);
/* ---------- ---------- */
  
  
  gtk_main();

  return 0;
}

void btn_zoom_in_clicked(GtkWidget *widget, gpointer data) {
  std::cout << "Aqui" << std::endl;
}

void btn_zoom_out_clicked(GtkWidget *widget, gpointer data) {
  std::cout << "Aqui" << std::endl;
}

void btn_up_clicked(GtkWidget *widget, gpointer data) {
  std::cout << "Aqui" << std::endl;
}

void btn_down_clicked(GtkWidget *widget, gpointer data) {
  std::cout << "Aqui" << std::endl;
}

void btn_left_clicked(GtkWidget *widget, gpointer data) {
  std::cout << "Aqui" << std::endl;
}

void btn_right_clicked(GtkWidget *widget, gpointer data) {
  std::cout << "Aqui" << std::endl;
}

void btn_ponto_clicked(GtkWidget *widget, gpointer data) {
  std::cout << "Aqui" << std::endl;
}

void btn_reta_clicked(GtkWidget *widget, gpointer data) {
  std::cout << "Aqui" << std::endl;
}

void btn_poligono_clicked(GtkWidget *widget, gpointer data) {
  std::cout << "Aqui" << std::endl;
}
