#include <gtk/gtk.h>

#include "controlador.hpp"
#include <iostream>

/* ---------- TELA PRINCIPAL ---------- */

GtkBuilder *builder;
GtkWidget *main_window;

/* ---------- AREA DE DESENHO E SUAS FUNCOES ---------- */

GtkWidget *displayArea;
static cairo_surface_t *surface = NULL;

static void clear_surface();
static gboolean configure_event_cb(GtkWidget *widget, GdkEventConfigure *event, gpointer data);
static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data);

/* ---------- LISTA OBJETO ---------- */
GtkCellRenderer *renderer;
GtkTreeView *tree_view;
GtkListStore *list_store;

void row_activated_lista_objeto(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *col, gpointer userdata);

/* ---------- MODAL DE EDICAO ---------- */
GtkWidget *edit_window;

GtkButton* btn_edit_voltar;
GtkButton* btn_edit_confirmar;

GtkEntry* entry_edit_nome;
GtkEntry* entry_translacao_x;
GtkEntry* entry_translacao_y;
GtkEntry* entry_escalonamento_x;
GtkEntry* entry_escalonamento_y;
GtkEntry* entry_rotacao_grau;

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


/* ---------- ENTRADAS MODAIS DE INCLUSAO ---------- */
GtkEntry* entry_ponto_nome;
GtkEntry* entry_ponto_x1;
GtkEntry* entry_ponto_y1;
GtkEntry* entry_ponto_z1;

GtkEntry* entry_reta_nome;
GtkEntry* entry_reta_inicio_x1;
GtkEntry* entry_reta_inicio_y1;
GtkEntry* entry_reta_inicio_z1;
GtkEntry* entry_reta_final_x1;
GtkEntry* entry_reta_final_y1;
GtkEntry* entry_reta_final_z1;

GtkEntry* entry_poligono_nome;
GtkEntry* entry_poligono_x1;
GtkEntry* entry_poligono_y1;
GtkEntry* entry_poligono_z1;

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

/* ---------- FUNCAO MODAL DE EDICAO ---------- */
void btn_edit_voltar_clicked(GtkWidget *widget, gpointer data);
void btn_edit_confirmar_clicked(GtkWidget *widget, gpointer data);

/* ---------- ---------- */

static Controlador *controlador;

int main (int argc, char *argv[]) {

  gtk_init(&argc, &argv);

  builder = gtk_builder_new();
  // TODO: add verificacao se pegou arquivo
  gtk_builder_add_from_file(builder, "src/ui.glade", nullptr);

  main_window = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
  g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

  displayArea = GTK_WIDGET(gtk_builder_get_object(builder, "displayArea"));
  g_signal_connect(displayArea, "draw", G_CALLBACK(draw_cb), nullptr);
  g_signal_connect(displayArea, "configure-event", G_CALLBACK(configure_event_cb), nullptr);

  gtk_widget_show(main_window);

  /* ---------- LISTA OBJETO ---------- */
  tree_view = GTK_TREE_VIEW( gtk_builder_get_object( builder, "objectTreeView" ) );
  list_store = GTK_LIST_STORE( gtk_builder_get_object( builder, "liststore1" ) );

  list_store = gtk_list_store_new (1, G_TYPE_STRING);

  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes(tree_view, -1, "Nome", renderer, "text", 0, NULL);

  gtk_tree_view_set_model (tree_view, GTK_TREE_MODEL (list_store));
  gtk_tree_view_column_set_min_width ( gtk_tree_view_get_column (tree_view, 0), 100 );
  gtk_tree_view_column_set_alignment ( gtk_tree_view_get_column (tree_view, 0), 0.5 );

  g_signal_connect(tree_view, "row-activated", G_CALLBACK(row_activated_lista_objeto), nullptr);

  /* ---------- MODAL DE EDICAO ---------- */
  edit_window = GTK_WIDGET(gtk_builder_get_object(builder, "editWindow"));

  btn_edit_voltar = GTK_BUTTON(gtk_builder_get_object(builder, "btnEditVoltar"));
  btn_edit_confirmar = GTK_BUTTON(gtk_builder_get_object(builder, "btnEditConfirmar"));

  g_signal_connect(btn_edit_voltar, "clicked", G_CALLBACK(btn_edit_voltar_clicked), nullptr);
  g_signal_connect(btn_edit_confirmar, "clicked", G_CALLBACK(btn_edit_confirmar_clicked), nullptr);

  entry_edit_nome = GTK_ENTRY(gtk_builder_get_object(builder, "entryEditNome"));
  entry_translacao_x = GTK_ENTRY(gtk_builder_get_object(builder, "entryTranslacaoX"));
  entry_translacao_y = GTK_ENTRY(gtk_builder_get_object(builder, "entryTranslacaoY"));
  entry_escalonamento_x = GTK_ENTRY(gtk_builder_get_object(builder, "entryEscalonamentoX"));
  entry_escalonamento_y = GTK_ENTRY(gtk_builder_get_object(builder, "entryEscalonamentoY"));
  entry_rotacao_grau = GTK_ENTRY(gtk_builder_get_object(builder, "entryRotacaoGrau"));

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

/* ---------- ENTRADAS MODAIS DE INCLUSAO ---------- */

  entry_ponto_nome = GTK_ENTRY(gtk_builder_get_object(builder, "entryPontoNome"));
  entry_ponto_x1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryPontoX1"));
  entry_ponto_y1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryPontoY1"));
  entry_ponto_z1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryPontoZ1"));

  entry_reta_nome = GTK_ENTRY(gtk_builder_get_object(builder, "entryRetaNome"));
  entry_reta_inicio_x1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryRetaInicioX1"));
  entry_reta_inicio_y1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryRetaInicioY1"));
  entry_reta_inicio_z1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryRetaInicioZ1"));
  entry_reta_final_x1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryRetaFinalX1"));
  entry_reta_final_y1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryRetaFinalY1"));
  entry_reta_final_z1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryRetaFinalZ1"));

  entry_poligono_nome = GTK_ENTRY(gtk_builder_get_object(builder, "entryPoligonoNome"));
  entry_poligono_x1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryPoligonoX1"));
  entry_poligono_y1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryPoligonoY1"));
  entry_poligono_z1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryPoligonoZ1"));

  /* ---------- ---------- */

  auto window = new Window(Coordenada(0,0), Coordenada(500, 500));
  auto viewport = new Viewport(surface, 0, 0, 500, 500);
  auto display_file = new DisplayFile();

  controlador = new Controlador(display_file, window, viewport, list_store);

  gtk_main();

  return 0;
}

void btn_zoom_in_clicked(GtkWidget *widget, gpointer data) {
  controlador->zoom(direcao_zoom_t::IN);
}

void btn_zoom_out_clicked(GtkWidget *widget, gpointer data) {
  controlador->zoom(direcao_zoom_t::OUT);
}

void btn_up_clicked(GtkWidget *widget, gpointer data) {
  controlador->navagacao(direcao_navegacao_t::UP);
}

void btn_down_clicked(GtkWidget *widget, gpointer data) {
  controlador->navagacao(direcao_navegacao_t::DOWN);
}

void btn_left_clicked(GtkWidget *widget, gpointer data) {
  controlador->navagacao(direcao_navegacao_t::LEFT);
}

void btn_right_clicked(GtkWidget *widget, gpointer data) {
  controlador->navagacao(direcao_navegacao_t::RIGHT);
}

void btn_ponto_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_show(ponto_window);
}

void btn_reta_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_show(reta_window);
}

void btn_poligono_clicked(GtkWidget *widget, gpointer data) {
  controlador->adicionar_poligono(operacao_poligono_t::NOVO, 0, 0,0);
  gtk_widget_show(plgn_window);
}

void btn_reta_voltar_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(reta_window);
}

void btn_ponto_voltar_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(ponto_window);
}

void btn_plgn_voltar_clicked(GtkWidget *widget, gpointer data) {
  controlador->adicionar_poligono(operacao_poligono_t::CANCELAR, 0, 0,0);
  gtk_widget_hide(plgn_window);
}

void btn_reta_incluir_clicked(GtkWidget *widget, gpointer data) {
  auto nome = gtk_entry_get_text(entry_reta_nome); 
  auto x1 = atof(gtk_entry_get_text(entry_reta_inicio_x1));
  auto y1 = atof(gtk_entry_get_text(entry_reta_inicio_y1));

  auto x2 = atof(gtk_entry_get_text(entry_reta_final_x1));
  auto y2 = atof(gtk_entry_get_text(entry_reta_final_y1));


  gtk_entry_set_text(entry_reta_nome,"");
  gtk_entry_set_text(entry_reta_inicio_x1,"");
  gtk_entry_set_text(entry_reta_inicio_y1,"");
  gtk_entry_set_text(entry_reta_inicio_z1,"");
  gtk_entry_set_text(entry_reta_final_x1,"");
  gtk_entry_set_text(entry_reta_final_y1,"");
  gtk_entry_set_text(entry_reta_final_z1,"");


  controlador->adicionar_reta(nome, x1, y1, x2, y2);
}

void btn_ponto_incluir_clicked(GtkWidget *widget, gpointer data) {
  auto nome = gtk_entry_get_text(entry_ponto_nome); 
  auto x1 = atof(gtk_entry_get_text(entry_ponto_x1));
  auto y1 = atof(gtk_entry_get_text(entry_ponto_y1));

  gtk_entry_set_text(entry_ponto_nome,"");
  gtk_entry_set_text(entry_ponto_x1,"");
  gtk_entry_set_text(entry_ponto_y1,"");
  gtk_entry_set_text(entry_ponto_z1,"");

  controlador->adicionar_ponto(nome, x1, y1);

}

void btn_plgn_incluir_clicked(GtkWidget *widget, gpointer data) {

  auto nome = gtk_entry_get_text(entry_poligono_nome); 

  gtk_entry_set_text(entry_poligono_nome,"");
  gtk_entry_set_text(entry_poligono_x1,"");
  gtk_entry_set_text(entry_poligono_y1,"");
  gtk_entry_set_text(entry_poligono_z1,"");

  controlador->adicionar_poligono(operacao_poligono_t::CONCLUIR, nome, 0, 0);
  controlador->adicionar_poligono(operacao_poligono_t::NOVO, 0, 0, 0);

}

void btn_plgn_add_ponto_clicked(GtkWidget *widget, gpointer data) {

  auto x1 = atof(gtk_entry_get_text(entry_poligono_x1));
  auto y1 = atof(gtk_entry_get_text(entry_poligono_y1));

  gtk_entry_set_text(entry_poligono_x1,"");
  gtk_entry_set_text(entry_poligono_y1,"");
  gtk_entry_set_text(entry_poligono_z1,"");

  controlador->adicionar_poligono(operacao_poligono_t::ADICIONAR_PONTO, 0, x1, y1);

}

void btn_edit_voltar_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(edit_window);
}

void btn_edit_confirmar_clicked(GtkWidget *widget, gpointer data) {

  gtk_widget_hide(edit_window);
}


static void clear_surface() {
  cairo_t *cr;

  cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_paint (cr);

  cairo_destroy (cr);
}

static gboolean configure_event_cb(GtkWidget *widget, GdkEventConfigure *event, gpointer data) {

  if (surface) {
    cairo_surface_destroy(surface);
  }

  surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget),
                                              CAIRO_CONTENT_COLOR,
                                              gtk_widget_get_allocated_width(widget),
                                              gtk_widget_get_allocated_height (widget));
  clear_surface();

  return TRUE;
}

static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data) {

  cairo_set_source_surface(cr, surface, 0, 0);
  cairo_paint(cr);
  gtk_widget_queue_draw(widget);

  return FALSE;
}

void row_activated_lista_objeto(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *col, gpointer userdata) {

  GtkTreeModel *model;
  GtkTreeIter   iter;

  model = gtk_tree_view_get_model(treeview);
  if (gtk_tree_model_get_iter(model, &iter, path)) {
      gchar *nome;
      gtk_tree_model_get(model, &iter, 0, &nome, -1);
      controlador->selecionar_objeto(nome);
      gtk_widget_show(edit_window);
  }
}
