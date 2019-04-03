#ifndef CONTROLADOR
#define CONTROLADOR

#include "coordenada.hpp"
#include "objeto.hpp"
#include "ponto.hpp"
#include "reta.hpp"
#include "poligono.hpp"
#include "display_file.hpp"
#include "window.hpp"
#include "viewport.hpp"

#include <gtk/gtk.h>


enum operacao_poligono_t {
    NOVO, ADICIONAR_PONTO, CONCLUIR, CANCELAR
};

class Controlador {


    public:

        Controlador(DisplayFile* display_file, Window *window, Viewport *viewport, GtkListStore* list_store):
            _list_store(list_store),
            _display_file(display_file), _window(window), _viewport(viewport),
            _coordenada_poligono(new std::vector<Coordenada>()) {}

        void adicionar_ponto(const char* nome,double x, double y);
        void adicionar_reta(const char* nome, double x1, double y1, double x2, double y2);
        void adicionar_poligono(operacao_poligono_t operacao, const char* nome, double x, double y);

        void zoom(direcao_zoom_t direcao, double escalar);

        void navagacao(direcao_navegacao_t direcao);

        void atualizar_tela();       
        void limpar_tela();

        void adicionar_objeto_na_tree_view(const char* nome);

    private:

        DisplayFile *_display_file;
        Window *_window;
        Viewport *_viewport;

        std::vector<Coordenada> *_coordenada_poligono;       

        GtkListStore * _list_store;
};

void Controlador::adicionar_ponto(const char* nome, double x, double y) {
    auto obj = new Ponto(nome, Coordenada(x,y));
    _display_file->adicionar_objeto(*obj);

    _viewport->desenhar_ponto(*obj, *_window);

    adicionar_objeto_na_tree_view(obj->nome().c_str());

}

void Controlador::adicionar_reta(const char* nome, double x1, double y1, double x2, double y2) {
    auto reta = new Reta(nome, Coordenada(x1,y1), Coordenada(x2,y2));
    _display_file->adicionar_objeto(*reta);
    _viewport->desenhar(*reta, *_window);

    adicionar_objeto_na_tree_view(reta->nome().c_str());

}

void Controlador::adicionar_poligono(operacao_poligono_t operacao, const char* nome, double x, double y) {
    Poligono* poligono;
    Objeto* obj;

    switch (operacao)
    {
        case NOVO:
            if (!_coordenada_poligono->empty())
                _coordenada_poligono->empty();

            _coordenada_poligono = new std::vector<Coordenada>();
            break;

        case ADICIONAR_PONTO:
            _coordenada_poligono->push_back(Coordenada(x,y));
            break;

        case CONCLUIR:
            if (_coordenada_poligono->size() < 1)
                return;

            poligono = new Poligono(nome);
            for(size_t i = 0; i < _coordenada_poligono->size(); i++) {
                poligono->adicionar_coordenada(
                    _coordenada_poligono->at(i).valor(0), _coordenada_poligono->at(i).valor(1)
                );
            }

            _coordenada_poligono->clear();
            _display_file->adicionar_objeto(*poligono);
            obj = poligono;
            _viewport->desenhar(*obj, *_window);

            adicionar_objeto_na_tree_view(obj->nome().c_str());
            break;

        case CANCELAR:
            _coordenada_poligono->clear();
            break;

        default:
            break;
    }

}

void Controlador::zoom(direcao_zoom_t direcao, double escalar) {
    // IMPLEMENTAR

    switch (direcao)
    {
        case IN:
            break;
        case OUT:
            break;

        default:
            break;
    }
}

void Controlador::navagacao(direcao_navegacao_t direcao) {
    _window->navagacao(direcao, 10);

    atualizar_tela();
}

void Controlador::atualizar_tela() {
    limpar_tela();

    for(size_t i = 0; i < _display_file->tamanho(); i++) {
        auto obj = _display_file->objeto(i);
        _viewport->desenhar(obj, *_window);
    }
}

void Controlador::limpar_tela() {
    _viewport->limpar_tela();
}


void Controlador::adicionar_objeto_na_tree_view(const char* nome) {
  GtkTreeIter iter;

  gtk_list_store_append(_list_store, &iter);
  gtk_list_store_set(_list_store, &iter, 0, nome, -1);
}


#endif
