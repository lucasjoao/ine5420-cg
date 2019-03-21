#include <gtk/gtk.h>
#include "objeto.hpp"
#include "ponto.hpp"
#include "reta.hpp"
#include "poligono.hpp"
#include <iostream>

/* ---------- TELA PRINCIPAL ---------- */

GtkBuilder *builder;
GtkWidget *main_window;

/* ---------- MODAIS DE INCLUSAO ---------- */

GtkWidget *reta_window;
GtkWidget *ponto_window;
GtkWidget *plgn_window;

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

/* ---------- BOTOES MODAIS DE INCLUSAO ---------- */

GtkButton* btn_reta_voltar;
GtkButton* btn_reta_incluir;

GtkButton* btn_ponto_voltar;
GtkButton* btn_ponto_incluir;

GtkButton* btn_plgn_voltar;
GtkButton* btn_plgn_incluir;
GtkButton* btn_plgn_add_ponto;

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

/* ---------- FUNCOES DOS BOTOES DOS MODAIS DE INCLUSAO ---------- */

void btn_reta_voltar_clicked(GtkWidget *widget, gpointer data);
void btn_reta_incluir_clicked(GtkWidget *widget, gpointer data);

void btn_ponto_voltar_clicked(GtkWidget *widget, gpointer data);
void btn_ponto_incluir_clicked(GtkWidget *widget, gpointer data);

void btn_plgn_voltar_clicked(GtkWidget *widget, gpointer data);
void btn_plgn_incluir_clicked(GtkWidget *widget, gpointer data);
void btn_plgn_add_ponto_clicked(GtkWidget *widget, gpointer data);

/* ---------- ---------- */



int main (int argc, char *argv[]) {

  gtk_init(&argc, &argv);

  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "src/ui.glade", nullptr);

  main_window = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
  g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

  gtk_widget_show(main_window);

  /* ---------- MODAIS DE INCLUSAO ---------- */

  reta_window = GTK_WIDGET(gtk_builder_get_object(builder, "retaWindow"));
  ponto_window = GTK_WIDGET(gtk_builder_get_object(builder, "pontoWindow"));
  plgn_window = GTK_WIDGET(gtk_builder_get_object(builder, "poligonoWindow"));

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

  g_signal_connect(btn_zoom_in, "clicked", G_CALLBACK(btn_zoom_in_clicked), nullptr);
  g_signal_connect(btn_zoom_out, "clicked", G_CALLBACK(btn_zoom_out_clicked), nullptr);
  g_signal_connect(btn_up, "clicked", G_CALLBACK(btn_up_clicked), nullptr);
  g_signal_connect(btn_down, "clicked", G_CALLBACK(btn_down_clicked), nullptr);
  g_signal_connect(btn_left, "clicked", G_CALLBACK(btn_left_clicked), nullptr);
  g_signal_connect(btn_right, "clicked", G_CALLBACK(btn_right_clicked), nullptr);
  g_signal_connect(btn_ponto, "clicked", G_CALLBACK(btn_ponto_clicked), nullptr);
  g_signal_connect(btn_reta, "clicked", G_CALLBACK(btn_reta_clicked), nullptr);
  g_signal_connect(btn_poligono, "clicked", G_CALLBACK(btn_poligono_clicked), nullptr);

  /* ---------- BOTOES TELA PRINCIPAL ---------- */

  btn_reta_voltar = GTK_BUTTON(gtk_builder_get_object(builder, "btnRetaVoltar"));
  btn_reta_incluir = GTK_BUTTON(gtk_builder_get_object(builder, "btnRetaIncluir"));
  btn_ponto_voltar = GTK_BUTTON(gtk_builder_get_object(builder, "btnPontoVoltar"));
  btn_ponto_incluir = GTK_BUTTON(gtk_builder_get_object(builder, "btnPontoIncluir"));
  btn_plgn_voltar = GTK_BUTTON(gtk_builder_get_object(builder, "btnPoligonoVoltar"));
  btn_plgn_incluir = GTK_BUTTON(gtk_builder_get_object(builder, "btnPoligonoIncluir"));
  btn_plgn_add_ponto = GTK_BUTTON(gtk_builder_get_object(builder, "btnAddPontoPoligono"));

  g_signal_connect(btn_reta_voltar, "clicked", G_CALLBACK(btn_reta_voltar_clicked), nullptr);
  g_signal_connect(btn_reta_incluir, "clicked", G_CALLBACK(btn_reta_incluir_clicked), nullptr);
  g_signal_connect(btn_ponto_voltar, "clicked", G_CALLBACK(btn_ponto_voltar_clicked), nullptr);
  g_signal_connect(btn_ponto_incluir, "clicked", G_CALLBACK(btn_ponto_incluir_clicked), nullptr);
  g_signal_connect(btn_plgn_voltar, "clicked", G_CALLBACK(btn_plgn_voltar_clicked), nullptr);
  g_signal_connect(btn_plgn_incluir, "clicked", G_CALLBACK(btn_plgn_incluir_clicked), nullptr);
  g_signal_connect(btn_plgn_add_ponto, "clicked", G_CALLBACK(btn_plgn_add_ponto_clicked), nullptr);

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
  gtk_widget_show(ponto_window);
}

void btn_reta_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_show(reta_window);
}

void btn_poligono_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_show(plgn_window);
}

void btn_reta_voltar_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(reta_window);
}

void btn_ponto_voltar_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(ponto_window);
}

void btn_plgn_voltar_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(plgn_window);
}

void btn_reta_incluir_clicked(GtkWidget *widget, gpointer data) {
  std::cout << "Aqui" << std::endl;
}

void btn_ponto_incluir_clicked(GtkWidget *widget, gpointer data) {
  std::cout << "Aqui" << std::endl;
}

void btn_plgn_incluir_clicked(GtkWidget *widget, gpointer data) {
  std::cout << "Aqui" << std::endl;
}

void btn_plgn_add_ponto_clicked(GtkWidget *widget, gpointer data) {
  std::cout << "Aqui" << std::endl;
}
