#include <gtk/gtk.h>

#include "controlador.hpp"
#include <iostream>

/* ---------- TELA PRINCIPAL ---------- */

GtkBuilder *builder;
GtkWidget *main_window;

/* ---------- CONSOLE PARA LOG ---------- */

GtkWidget *txtConsole;
GtkScrolledWindow *scrolledConsole;

void show_mensagem_console(std::string msg);

/* ----------- ESCOLHA DO CLIPPING DE RETA ------------ */

GtkToggleButton *cb_alg_liang_barsky;
GtkToggleButton *cb_alg_cohen_sutherland;

void choose_liang_barsky(GtkToggleButton *toggle_button, gpointer user_data);
void choose_cohen_sutherland(GtkToggleButton *toggle_button, gpointer user_data);

/* ---------- AREA DE DESENHO E SUAS FUNCOES ---------- */

GtkWidget *displayArea;
static cairo_surface_t *surface = NULL;

static void clear_surface();
static gboolean configure_event_cb(GtkWidget *widget, GdkEventConfigure *event, gpointer data);
static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data);

/* ---------- ARQUIVOS ---------- */
GtkButton* btn_save_file;
GtkButton* btn_load_file;

/* ---------- ROTACAO WINDOW ---------- */
GtkEntry* entry_rot_window;
GtkButton* btn_rotacao_window_ok;

void btn_rotacao_window_ok_clicked(GtkWidget *widget, gpointer data);

/* ---------- LISTA OBJETO ---------- */
GtkCellRenderer *renderer;
GtkTreeView *tree_view;
GtkListStore *list_store;

void row_activated_lista_objeto(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *col, gpointer userdata);

/* ---------- MODAL DE EDICAO ---------- */
GtkWidget *edit_window;

GtkButton* btn_edit_voltar;
GtkButton* btn_edit_confirmar;

GtkButton* btn_rot_mundo;
GtkButton* btn_rot_obj;
GtkButton* btn_rot_pnt;

GtkEntry* entry_translacao_x;
GtkEntry* entry_translacao_y;

GtkEntry* entry_escalonamento_x;
GtkEntry* entry_escalonamento_y;

/* ---------- MODAIS DE ROTACAO ---------- */
GtkWidget *rot_mundo_window;
GtkWidget *rot_obj_window;
GtkWidget *rot_pnt_window;

/* ---------- MODAIS DE INCLUSAO ---------- */

GtkWidget *reta_window;
GtkWidget *ponto_window;
GtkWidget *plgn_window;
GtkWidget *curva_window;
/* ---------- BOTOES TELA PRINCIPAL ---------- */

GtkButton* btn_zoom_in;
GtkButton* btn_zoom_out;

GtkButton* btn_up;
GtkButton* btn_down;
GtkButton* btn_left;
GtkButton* btn_right;

GtkButton* btn_clean_screen;

GtkButton* btn_ponto;
GtkButton* btn_reta;
GtkButton* btn_poligono;
GtkButton* btn_curva;
/* ---------- BOTOES MODAIS DE INCLUSAO ---------- */

GtkButton* btn_reta_voltar;
GtkButton* btn_reta_incluir;

GtkButton* btn_ponto_voltar;
GtkButton* btn_ponto_incluir;

GtkButton* btn_plgn_voltar;
GtkButton* btn_plgn_incluir;
GtkButton* btn_plgn_add_ponto;

GtkButton* btn_curva_voltar;
GtkButton* btn_curva_incluir;
GtkButton* btn_curva_add_ponto;
GtkRadioButton* radio_curva_bezier;
GtkRadioButton* radio_curva_bspline;

/* ---------- BOTOES MODAIS DE ROTACAO ---------- */

GtkButton* btn_rot_mundo_voltar;
GtkButton* btn_rot_mundo_rotacionar;

GtkButton* btn_rot_obj_voltar;
GtkButton* btn_rot_obj_rotacionar;

GtkButton* btn_rot_pnt_voltar;
GtkButton* btn_rot_pnt_rotacionar;

/* ---------- LABELS MODAIS DE INCLUSAO ---------- */
GtkLabel* lbl_quantidade_ponto_curva;

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
GtkToggleButton *cb_plgn_preenchido;

GtkEntry* entry_curva_nome;
GtkEntry* entry_curva_x1;
GtkEntry* entry_curva_y1;
GtkEntry* entry_curva_z1;

/* ---------- ENTRADAS MODAIS DE ROTACAO ---------- */;
GtkEntry* entry_rot_mundo;
GtkEntry* entry_rot_obj;
GtkEntry* entry_rot_pnt_graus;
GtkEntry* entry_rot_pnt_x1;
GtkEntry* entry_rot_pnt_y1;

/* ---------- FUNCOES DOS BOTOES DE ARQUIVOS ---------- */
void btn_save_file_clicked(GtkWidget *widget, gpointer data);
void btn_load_file_clicked(GtkWidget *widget, gpointer data);

/* ---------- FUNCOES DOS BOTOES DA TELA PRINCIPAL ---------- */

void btn_zoom_in_clicked(GtkWidget *widget, gpointer data);
void btn_zoom_out_clicked(GtkWidget *widget, gpointer data);

void btn_up_clicked(GtkWidget *widget, gpointer data);
void btn_down_clicked(GtkWidget *widget, gpointer data);
void btn_left_clicked(GtkWidget *widget, gpointer data);
void btn_right_clicked(GtkWidget *widget, gpointer data);

void btn_clean_screen_clicked(GtkWidget *widget, gpointer data);

void btn_ponto_clicked(GtkWidget *widget, gpointer data);
void btn_reta_clicked(GtkWidget *widget, gpointer data);
void btn_poligono_clicked(GtkWidget *widget, gpointer data);
void btn_curva_clicked(GtkWidget *widget, gpointer data);
/* ---------- FUNCOES DOS BOTOES DOS MODAIS DE INCLUSAO ---------- */

void btn_reta_voltar_clicked(GtkWidget *widget, gpointer data);
void btn_reta_incluir_clicked(GtkWidget *widget, gpointer data);

void btn_ponto_voltar_clicked(GtkWidget *widget, gpointer data);
void btn_ponto_incluir_clicked(GtkWidget *widget, gpointer data);

void btn_plgn_voltar_clicked(GtkWidget *widget, gpointer data);
void btn_plgn_incluir_clicked(GtkWidget *widget, gpointer data);
void btn_plgn_add_ponto_clicked(GtkWidget *widget, gpointer data);
void cb_plgn_preenchido_toggled(GtkToggleButton *toggle_button, gpointer user_data);

void btn_curva_voltar_clicked(GtkWidget *widget, gpointer data);
void btn_curva_incluir_clicked(GtkWidget *widget, gpointer data);
void btn_curva_add_ponto_clicked(GtkWidget *widget, gpointer data);

/* ---------- FUNCAO MODAL DE EDICAO ---------- */
void btn_edit_voltar_clicked(GtkWidget *widget, gpointer data);
void btn_edit_confirmar_clicked(GtkWidget *widget, gpointer data);
void btn_rot_mundo_clicked(GtkWidget *widget, gpointer data);
void btn_rot_obj_clicked(GtkWidget *widget, gpointer data);
void btn_rot_pnt_clicked(GtkWidget *widget, gpointer data);

/* ---------- FUNCOES MODAIS DE ROTACAO ---------- */
void btn_rot_mundo_voltar_clicked(GtkWidget *widget, gpointer data);
void btn_rot_mundo_rotacionar_clicked(GtkWidget *widget, gpointer data);

void btn_rot_obj_voltar_clicked(GtkWidget *widget, gpointer data);
void btn_rot_obj_rotacionar_clicked(GtkWidget *widget, gpointer data);

void btn_rot_pnt_voltar_clicked(GtkWidget *widget, gpointer data);
void btn_rot_pnt_rotacionar_clicked(GtkWidget *widget, gpointer data);

/* ---------- ---------- */

static Controlador *controlador;

int main (int argc, char *argv[]) {

  gtk_init(&argc, &argv);

  builder = gtk_builder_new();
  GError *err = nullptr;
  gtk_builder_add_from_file(builder, "src/ui.glade", &err);
  if (err != nullptr) {
    fprintf(stderr, "Não foi possível ler o arquivo: %s\n", err->message);
    g_error_free(err);
    return 1;
  }

  main_window = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
  g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

  displayArea = GTK_WIDGET(gtk_builder_get_object(builder, "displayArea"));
  g_signal_connect(displayArea, "draw", G_CALLBACK(draw_cb), nullptr);
  g_signal_connect(displayArea, "configure-event", G_CALLBACK(configure_event_cb), nullptr);

  gtk_widget_show(main_window);

  /* ---------- CONSOLE PARA LOG ---------- */

  txtConsole = GTK_WIDGET(gtk_builder_get_object(builder, "txtConsole"));
  scrolledConsole = GTK_SCROLLED_WINDOW(gtk_builder_get_object(builder, "scrolledConsole"));

  /* ---------- ARQUIVOS ---------- */
  btn_save_file = GTK_BUTTON(gtk_builder_get_object(builder, "btnSave"));
  btn_load_file = GTK_BUTTON(gtk_builder_get_object(builder, "btnImport"));

  g_signal_connect(btn_save_file, "clicked", G_CALLBACK(btn_save_file_clicked), nullptr);
  g_signal_connect(btn_load_file, "clicked", G_CALLBACK(btn_load_file_clicked), nullptr);

  /* ---------- ROTACAO WINDOW ---------- */
  entry_rot_window = GTK_ENTRY(gtk_builder_get_object(builder, "entryRotacaoWindow"));

  btn_rotacao_window_ok = GTK_BUTTON(gtk_builder_get_object(builder, "btnRotacaoWindowOk"));
  g_signal_connect(btn_rotacao_window_ok, "clicked", G_CALLBACK(btn_rotacao_window_ok_clicked), nullptr);

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
  btn_rot_mundo = GTK_BUTTON(gtk_builder_get_object(builder, "btnRotacaoMundo"));
  btn_rot_obj = GTK_BUTTON(gtk_builder_get_object(builder, "btnRotacaoObjeto"));
  btn_rot_pnt = GTK_BUTTON(gtk_builder_get_object(builder, "btnRotacaoQualquer"));

  g_signal_connect(btn_edit_voltar, "clicked", G_CALLBACK(btn_edit_voltar_clicked), nullptr);
  g_signal_connect(btn_edit_confirmar, "clicked", G_CALLBACK(btn_edit_confirmar_clicked), nullptr);
  g_signal_connect(btn_rot_mundo, "clicked", G_CALLBACK(btn_rot_mundo_clicked), nullptr);
  g_signal_connect(btn_rot_obj, "clicked", G_CALLBACK(btn_rot_obj_clicked), nullptr);
  g_signal_connect(btn_rot_pnt, "clicked", G_CALLBACK(btn_rot_pnt_clicked), nullptr);

  entry_translacao_x = GTK_ENTRY(gtk_builder_get_object(builder, "entryTranslacaoX"));
  entry_translacao_y = GTK_ENTRY(gtk_builder_get_object(builder, "entryTranslacaoY"));

  entry_escalonamento_x = GTK_ENTRY(gtk_builder_get_object(builder, "entryEscalonamentoX"));
  entry_escalonamento_y = GTK_ENTRY(gtk_builder_get_object(builder, "entryEscalonamentoY"));

  /* ---------- MODAIS DE INCLUSAO ---------- */

  reta_window = GTK_WIDGET(gtk_builder_get_object(builder, "retaWindow"));
  ponto_window = GTK_WIDGET(gtk_builder_get_object(builder, "pontoWindow"));
  plgn_window = GTK_WIDGET(gtk_builder_get_object(builder, "poligonoWindow"));
  curva_window = GTK_WIDGET(gtk_builder_get_object(builder, "curvaWindow"));

  /* ---------- MODAIS DE ROTACAO ---------- */

  rot_mundo_window = GTK_WIDGET(gtk_builder_get_object(builder, "rotMundoWindow"));
  rot_obj_window = GTK_WIDGET(gtk_builder_get_object(builder, "rotObjetoWindow"));
  rot_pnt_window = GTK_WIDGET(gtk_builder_get_object(builder, "rotPntQlqWindow"));

  /* ---------- BOTOES TELA PRINCIPAL ---------- */

  btn_zoom_in = GTK_BUTTON(gtk_builder_get_object(builder, "btnZoomIn"));
  btn_zoom_out = GTK_BUTTON(gtk_builder_get_object(builder, "btnZoomOut"));
  btn_up = GTK_BUTTON(gtk_builder_get_object(builder, "btnUp"));
  btn_down = GTK_BUTTON(gtk_builder_get_object(builder, "btnDown"));
  btn_left = GTK_BUTTON(gtk_builder_get_object(builder, "btnLeft"));
  btn_right = GTK_BUTTON(gtk_builder_get_object(builder, "btnRight"));
  btn_clean_screen = GTK_BUTTON(gtk_builder_get_object(builder, "btnClean"));
  btn_ponto = GTK_BUTTON(gtk_builder_get_object(builder, "btnPonto"));
  btn_reta = GTK_BUTTON(gtk_builder_get_object(builder, "btnReta"));
  btn_poligono = GTK_BUTTON(gtk_builder_get_object(builder, "btnPoligono"));
  btn_curva = GTK_BUTTON(gtk_builder_get_object(builder, "btnCurva"));

  g_signal_connect(btn_zoom_in, "clicked", G_CALLBACK(btn_zoom_in_clicked), nullptr);
  g_signal_connect(btn_zoom_out, "clicked", G_CALLBACK(btn_zoom_out_clicked), nullptr);
  g_signal_connect(btn_up, "clicked", G_CALLBACK(btn_up_clicked), nullptr);
  g_signal_connect(btn_down, "clicked", G_CALLBACK(btn_down_clicked), nullptr);
  g_signal_connect(btn_left, "clicked", G_CALLBACK(btn_left_clicked), nullptr);
  g_signal_connect(btn_right, "clicked", G_CALLBACK(btn_right_clicked), nullptr);
  g_signal_connect(btn_clean_screen, "clicked", G_CALLBACK(btn_clean_screen_clicked), nullptr);
  g_signal_connect(btn_ponto, "clicked", G_CALLBACK(btn_ponto_clicked), nullptr);
  g_signal_connect(btn_reta, "clicked", G_CALLBACK(btn_reta_clicked), nullptr);
  g_signal_connect(btn_poligono, "clicked", G_CALLBACK(btn_poligono_clicked), nullptr);
  g_signal_connect(btn_curva, "clicked", G_CALLBACK(btn_curva_clicked), nullptr);

  /* ---------- LABELS MODAIS DE INCLUSAO ---------- */
  lbl_quantidade_ponto_curva = GTK_LABEL(gtk_builder_get_object(builder, "lblQuantidadePontoCurva"));

  /* ---------- BOTOES MODAIS DE INCLUSAO ---------- */

  btn_reta_voltar = GTK_BUTTON(gtk_builder_get_object(builder, "btnRetaVoltar"));
  btn_reta_incluir = GTK_BUTTON(gtk_builder_get_object(builder, "btnRetaIncluir"));
  btn_ponto_voltar = GTK_BUTTON(gtk_builder_get_object(builder, "btnPontoVoltar"));
  btn_ponto_incluir = GTK_BUTTON(gtk_builder_get_object(builder, "btnPontoIncluir"));
  btn_plgn_voltar = GTK_BUTTON(gtk_builder_get_object(builder, "btnPoligonoVoltar"));
  btn_plgn_incluir = GTK_BUTTON(gtk_builder_get_object(builder, "btnPoligonoIncluir"));
  btn_plgn_add_ponto = GTK_BUTTON(gtk_builder_get_object(builder, "btnAddPontoPoligono"));
  cb_plgn_preenchido =  GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "cbPoligonoPreenchido"));
  btn_curva_voltar = GTK_BUTTON(gtk_builder_get_object(builder, "btnCurvaVoltar"));
  btn_curva_incluir = GTK_BUTTON(gtk_builder_get_object(builder, "btnCurvaIncluir"));
  btn_curva_add_ponto = GTK_BUTTON(gtk_builder_get_object(builder, "btnAddPontoCurva"));

  g_signal_connect(btn_reta_voltar, "clicked", G_CALLBACK(btn_reta_voltar_clicked), nullptr);
  g_signal_connect(btn_reta_incluir, "clicked", G_CALLBACK(btn_reta_incluir_clicked), nullptr);
  g_signal_connect(btn_ponto_voltar, "clicked", G_CALLBACK(btn_ponto_voltar_clicked), nullptr);
  g_signal_connect(btn_ponto_incluir, "clicked", G_CALLBACK(btn_ponto_incluir_clicked), nullptr);
  g_signal_connect(btn_plgn_voltar, "clicked", G_CALLBACK(btn_plgn_voltar_clicked), nullptr);
  g_signal_connect(btn_plgn_incluir, "clicked", G_CALLBACK(btn_plgn_incluir_clicked), nullptr);
  g_signal_connect(btn_plgn_add_ponto, "clicked", G_CALLBACK(btn_plgn_add_ponto_clicked), nullptr);
  g_signal_connect(cb_plgn_preenchido, "toggled", G_CALLBACK(cb_plgn_preenchido_toggled), nullptr);
  g_signal_connect(btn_curva_voltar, "clicked", G_CALLBACK(btn_curva_voltar_clicked), nullptr);
  g_signal_connect(btn_curva_incluir, "clicked", G_CALLBACK(btn_curva_incluir_clicked), nullptr);
  g_signal_connect(btn_curva_add_ponto, "clicked", G_CALLBACK(btn_curva_add_ponto_clicked), nullptr);

  /* ---------- BOTOES MODAIS DE ROTACAO ---------- */

  btn_rot_mundo_voltar = GTK_BUTTON(gtk_builder_get_object(builder, "btnRotMundoVoltar"));
  btn_rot_mundo_rotacionar = GTK_BUTTON(gtk_builder_get_object(builder, "btnRotMundoRotacionar"));
  btn_rot_obj_voltar = GTK_BUTTON(gtk_builder_get_object(builder, "btnRotObjetoVoltar"));
  btn_rot_obj_rotacionar = GTK_BUTTON(gtk_builder_get_object(builder, "btnRotObjetoRotacionar"));
  btn_rot_pnt_voltar = GTK_BUTTON(gtk_builder_get_object(builder, "btnRotPntQlqVoltar"));
  btn_rot_pnt_rotacionar = GTK_BUTTON(gtk_builder_get_object(builder, "btnRotPntQlqRotacionar"));

  g_signal_connect(btn_rot_mundo_voltar, "clicked", G_CALLBACK(btn_rot_mundo_voltar_clicked), nullptr);
  g_signal_connect(btn_rot_mundo_rotacionar, "clicked", G_CALLBACK(btn_rot_mundo_rotacionar_clicked), nullptr);
  g_signal_connect(btn_rot_obj_voltar, "clicked", G_CALLBACK(btn_rot_obj_voltar_clicked), nullptr);
  g_signal_connect(btn_rot_obj_rotacionar, "clicked", G_CALLBACK(btn_rot_obj_rotacionar_clicked), nullptr);
  g_signal_connect(btn_rot_pnt_voltar, "clicked", G_CALLBACK(btn_rot_pnt_voltar_clicked), nullptr);
  g_signal_connect(btn_rot_pnt_rotacionar, "clicked", G_CALLBACK(btn_rot_pnt_rotacionar_clicked), nullptr);

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

  entry_curva_nome = GTK_ENTRY(gtk_builder_get_object(builder, "entryCurvaNome"));
  entry_curva_x1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryCurvaX1"));
  entry_curva_y1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryCurvaY1"));
  entry_curva_z1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryCurvaZ1"));
  radio_curva_bezier = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "radioCurvaBezier"));
  radio_curva_bspline = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "radioCurvaBSpline"));

  /* ---------- ENTRADAS MODAIS DE ROTACAO ---------- */

  entry_rot_mundo = GTK_ENTRY(gtk_builder_get_object(builder, "entryRotMundo"));
  entry_rot_obj = GTK_ENTRY(gtk_builder_get_object(builder, "entryRotObjeto"));
  entry_rot_pnt_graus = GTK_ENTRY(gtk_builder_get_object(builder, "entryGrausRotPntQlq"));
  entry_rot_pnt_x1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryRotPntQlqX1"));
  entry_rot_pnt_y1 = GTK_ENTRY(gtk_builder_get_object(builder, "entryRotPntQlqY2"));

  /* ----------- ESCOLHA DO CLIPPING DE RETA ------------ */

  cb_alg_cohen_sutherland = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "cb_alg_cohen_sutherland"));
  cb_alg_liang_barsky = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "cb_alg_liang_barsky"));

  g_signal_connect (cb_alg_cohen_sutherland, "toggled", G_CALLBACK (choose_cohen_sutherland), nullptr);
  g_signal_connect (cb_alg_liang_barsky, "toggled", G_CALLBACK (choose_liang_barsky), nullptr);

  /* ---------- ---------- */

  auto window = new Window(Coordenada(0,0), 480, 480);
  auto viewport = new Viewport(surface, 0, 0, 480, 480);
  auto display_file = new DisplayFile();

  controlador = new Controlador(display_file, window, viewport, list_store);
  gtk_main();

  return 0;
}

void show_mensagem_console(std::string msg) {
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txtConsole));
  GtkTextIter end;
  gtk_text_buffer_get_end_iter(buffer, &end);
  gtk_text_buffer_insert(buffer, &end, msg.c_str(), -1);
}

void btn_save_file_clicked(GtkWidget *widget, gpointer data) {
  GtkWidget *dialog;
  GtkFileChooser *chooser;

  dialog = gtk_file_chooser_dialog_new("Salvar arquivo",
                                        GTK_WINDOW(main_window),
                                        GTK_FILE_CHOOSER_ACTION_SAVE,
                                        "Cancelar",
                                        GTK_RESPONSE_CANCEL,
                                        "Salvar",
                                        GTK_RESPONSE_ACCEPT,
                                        nullptr);
  chooser = GTK_FILE_CHOOSER(dialog);

  gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);

  gtk_file_chooser_set_current_name(chooser, "arquivo.obj");

  if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
    controlador->salvar_arquivo(gtk_file_chooser_get_filename(chooser));
  }

  gtk_widget_destroy(dialog);
  show_mensagem_console("Arquivo .obj salvo!\n");
}

void btn_load_file_clicked(GtkWidget *widget, gpointer data) {
  GtkWidget *dialog;
  GtkFileChooser *chooser;

  dialog = gtk_file_chooser_dialog_new("Abrir arquivo",
                                        GTK_WINDOW(main_window),
                                        GTK_FILE_CHOOSER_ACTION_OPEN,
                                        "Cancelar",
                                        GTK_RESPONSE_CANCEL,
                                        "Abrir",
                                        GTK_RESPONSE_ACCEPT,
                                        nullptr);

  if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
    chooser = GTK_FILE_CHOOSER(dialog);
    controlador->carregar_arquivo(gtk_file_chooser_get_filename(chooser));
  }

  gtk_widget_destroy(dialog);
  show_mensagem_console("Tela 'limpada' e arquivo .obj carregado!\n");
}

void btn_rotacao_window_ok_clicked(GtkWidget *widget, gpointer data) {
  auto grau = atof(gtk_entry_get_text(entry_rot_window));

  if (grau) {
    controlador->rotacao_window(grau);
    show_mensagem_console("Window rotacionada " + std::to_string(grau) + " graus!\n");
  }
}

void btn_zoom_in_clicked(GtkWidget *widget, gpointer data) {
  controlador->zoom(direcao_zoom_t::IN);
  show_mensagem_console("Zoom in realizado!\n");
}

void btn_zoom_out_clicked(GtkWidget *widget, gpointer data) {
  controlador->zoom(direcao_zoom_t::OUT);
  show_mensagem_console("Zoom out realizado!\n");
}

void btn_up_clicked(GtkWidget *widget, gpointer data) {
  controlador->navagacao(direcao_navegacao_t::UP);
  show_mensagem_console("Movimentação para cima realizada!\n");
}

void btn_down_clicked(GtkWidget *widget, gpointer data) {
  controlador->navagacao(direcao_navegacao_t::DOWN);
  show_mensagem_console("Movimentação para baixo realizada!\n");
}

void btn_left_clicked(GtkWidget *widget, gpointer data) {
  controlador->navagacao(direcao_navegacao_t::LEFT);
  show_mensagem_console("Movimentação para esquerda realizada!\n");
}

void btn_right_clicked(GtkWidget *widget, gpointer data) {
  controlador->navagacao(direcao_navegacao_t::RIGHT);
  show_mensagem_console("Movimentação para direita realizada!\n");
}

void btn_clean_screen_clicked(GtkWidget *widget, gpointer data) {
  controlador->limpar_tela();
  show_mensagem_console("Tela 'limpada' com sucesso!\n");
}

void btn_ponto_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_show(ponto_window);
}

void btn_reta_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_show(reta_window);
}

void btn_poligono_clicked(GtkWidget *widget, gpointer data) {
  // evitar valores incorretos provenientes de arquivos
  gtk_toggle_button_set_active(cb_plgn_preenchido, controlador->get_poligono_preenchido());
  controlador->adicionar_poligono(operacao_obj_t::NOVO, "", 0, 0);
  gtk_widget_show(plgn_window);
}

void btn_reta_voltar_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(reta_window);
}

void btn_ponto_voltar_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(ponto_window);
}

void btn_plgn_voltar_clicked(GtkWidget *widget, gpointer data) {
  controlador->adicionar_poligono(operacao_obj_t::CANCELAR, "", 0, 0);
  gtk_widget_hide(plgn_window);
}

void btn_reta_incluir_clicked(GtkWidget *widget, gpointer data) {
  std::string nome = gtk_entry_get_text(entry_reta_nome);
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
  show_mensagem_console("Reta adicionada!\n");
}

void btn_ponto_incluir_clicked(GtkWidget *widget, gpointer data) {
  std::string nome = gtk_entry_get_text(entry_ponto_nome);
  auto x1 = atof(gtk_entry_get_text(entry_ponto_x1));
  auto y1 = atof(gtk_entry_get_text(entry_ponto_y1));

  gtk_entry_set_text(entry_ponto_nome,"");
  gtk_entry_set_text(entry_ponto_x1,"");
  gtk_entry_set_text(entry_ponto_y1,"");
  gtk_entry_set_text(entry_ponto_z1,"");

  controlador->adicionar_ponto(nome, x1, y1);
  show_mensagem_console("Ponto adicionado!\n");
}

void btn_plgn_incluir_clicked(GtkWidget *widget, gpointer data) {

  std::string nome = gtk_entry_get_text(entry_poligono_nome);

  gtk_entry_set_text(entry_poligono_nome,"");
  gtk_entry_set_text(entry_poligono_x1,"");
  gtk_entry_set_text(entry_poligono_y1,"");
  gtk_entry_set_text(entry_poligono_z1,"");

  controlador->adicionar_poligono(operacao_obj_t::CONCLUIR, nome, 0, 0);
  controlador->adicionar_poligono(operacao_obj_t::NOVO, "", 0, 0);
  show_mensagem_console("Polígono adicionado!\n");
}

void btn_plgn_add_ponto_clicked(GtkWidget *widget, gpointer data) {

  auto x1 = atof(gtk_entry_get_text(entry_poligono_x1));
  auto y1 = atof(gtk_entry_get_text(entry_poligono_y1));

  gtk_entry_set_text(entry_poligono_x1,"");
  gtk_entry_set_text(entry_poligono_y1,"");
  gtk_entry_set_text(entry_poligono_z1,"");

  controlador->adicionar_poligono(operacao_obj_t::ADICIONAR_PONTO, "", x1, y1);
  show_mensagem_console("Ponto adicionado para compor o polígono!\n");
}

void btn_curva_clicked(GtkWidget *widget, gpointer data) {
  controlador->adicionar_curva_novo();
  gtk_label_set_text(lbl_quantidade_ponto_curva,"Quantidade de ponto: 0");
  gtk_widget_show(curva_window);
}

void btn_curva_voltar_clicked(GtkWidget *widget, gpointer data) {
  controlador->adicionar_poligono(operacao_obj_t::CANCELAR, "", 0, 0);
  gtk_widget_hide(curva_window);
}

void btn_curva_incluir_clicked(GtkWidget *widget, gpointer data) {
  std::string nome = gtk_entry_get_text(entry_curva_nome);

  gtk_entry_set_text(entry_curva_nome,"");
  gtk_entry_set_text(entry_curva_x1,"");
  gtk_entry_set_text(entry_curva_y1,"");
  gtk_entry_set_text(entry_curva_z1,"");
  gtk_label_set_text(lbl_quantidade_ponto_curva,"Quantidade de ponto: 0");

  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_curva_bezier))) {
    controlador->adicionar_curva_concluir(tipo_t::CURVA_BEZIER, nome);
  } else {
    controlador->adicionar_curva_concluir(tipo_t::CURVA_BSPLINE, nome);
    show_mensagem_console("Curva bspline adicionada!\n");
  }

  controlador->adicionar_curva_novo();
}

void btn_curva_add_ponto_clicked(GtkWidget *widget, gpointer data) {
  auto x1 = atof(gtk_entry_get_text(entry_curva_x1));
  auto y1 = atof(gtk_entry_get_text(entry_curva_y1));

  gtk_entry_set_text(entry_curva_x1,"");
  gtk_entry_set_text(entry_curva_y1,"");
  gtk_entry_set_text(entry_curva_z1,"");

  controlador->adicionar_curva_adicionar_ponto(x1,y1);
  std::string text = "Quantidade de ponto: ";
  text += std::to_string(controlador->numero_pontos_obj());
  gtk_label_set_text(lbl_quantidade_ponto_curva, text.c_str());
}


void btn_edit_voltar_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(edit_window);
}

void btn_edit_confirmar_clicked(GtkWidget *widget, gpointer data) {

  auto Dx = atof(gtk_entry_get_text(entry_translacao_x));
  auto Dy = atof(gtk_entry_get_text(entry_translacao_y));

  auto Sx = atof(gtk_entry_get_text(entry_escalonamento_x));
  auto Sy = atof(gtk_entry_get_text(entry_escalonamento_y));

  if (Dx != 0 || Dy != 0) {
    controlador->editar_objeto_translacao(Dx, Dy);
  }

  if (Sx != 0 || Sy != 0) {
    controlador->editar_objeto_escalonamento(Sx, Sy);
  }

  gtk_entry_set_text(entry_translacao_x,"");
  gtk_entry_set_text(entry_translacao_y,"");

  gtk_entry_set_text(entry_escalonamento_x,"");
  gtk_entry_set_text(entry_escalonamento_y,"");

  gtk_widget_hide(edit_window);
  show_mensagem_console("Edição realizada com sucesso!\n");
}

void btn_rot_mundo_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(edit_window);
  gtk_widget_show(rot_mundo_window);
}

void btn_rot_obj_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(edit_window);
  gtk_widget_show(rot_obj_window);
}

void btn_rot_pnt_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(edit_window);
  gtk_widget_show(rot_pnt_window);
}

void btn_rot_mundo_voltar_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(rot_mundo_window);
  gtk_widget_show(edit_window);
}

void btn_rot_mundo_rotacionar_clicked(GtkWidget *widget, gpointer data) {
  auto graus = atof(gtk_entry_get_text(entry_rot_mundo));
  controlador->editar_objeto_rotacao_entorno_centro_mundo(graus);
  gtk_entry_set_text(entry_rot_mundo, "");
  gtk_widget_hide(rot_mundo_window);
  show_mensagem_console("Objeto rotacionado em torno do centro do mundo " + std::to_string(graus) + " graus!\n");
}

void btn_rot_obj_voltar_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(rot_obj_window);
  gtk_widget_show(edit_window);
}

void btn_rot_obj_rotacionar_clicked(GtkWidget *widget, gpointer data) {
  auto graus = atof(gtk_entry_get_text(entry_rot_obj));
  controlador->editar_objeto_rotacao_entorno_centro_objeto(graus);
  gtk_entry_set_text(entry_rot_obj, "");
  gtk_widget_hide(rot_obj_window);
  show_mensagem_console("Objeto rotacionado em torno do centro do objeto " + std::to_string(graus) + " graus!\n");
}

void btn_rot_pnt_voltar_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(rot_pnt_window);
  gtk_widget_show(edit_window);
}

void btn_rot_pnt_rotacionar_clicked(GtkWidget *widget, gpointer data) {
  auto graus = atof(gtk_entry_get_text(entry_rot_pnt_graus));
  auto x = atof(gtk_entry_get_text(entry_rot_pnt_x1));
  auto y = atof(gtk_entry_get_text(entry_rot_pnt_y1));

  controlador->editar_objeto_rotacao_entorno_centro_ponto(graus, x, y);

  gtk_entry_set_text(entry_rot_pnt_graus, "");
  gtk_entry_set_text(entry_rot_pnt_x1, "");
  gtk_entry_set_text(entry_rot_pnt_y1, "");

  gtk_widget_hide(rot_pnt_window);
  show_mensagem_console("Objeto rotacionado em torno de um ponto " + std::to_string(graus) + " graus!\n");
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

void choose_cohen_sutherland(GtkToggleButton *toggle_button, gpointer user_data) {
  controlador->selecionar_algoritmo_clipping_reta(0);
  gtk_toggle_button_set_active (cb_alg_liang_barsky, FALSE);
}

void choose_liang_barsky(GtkToggleButton *toggle_button, gpointer user_data) {
  controlador->selecionar_algoritmo_clipping_reta(1);
  gtk_toggle_button_set_active (cb_alg_cohen_sutherland, FALSE);
}

void cb_plgn_preenchido_toggled(GtkToggleButton *toggle_button, gpointer user_data) {
  auto valor = gtk_toggle_button_get_active(cb_plgn_preenchido);
  controlador->poligono_preenchido(valor);
}
