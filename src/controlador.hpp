#ifndef CONTROLADOR_HPP
#define CONTROLADOR_HPP

#include "coordenada.hpp"
#include "objeto.hpp"
#include "ponto.hpp"
#include "reta.hpp"
#include "poligono.hpp"
#include "display_file.hpp"
#include "window.hpp"
#include "viewport.hpp"
#include "transformacao.hpp"
#include <iostream>

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

        void zoom(direcao_zoom_t direca);
        void navagacao(direcao_navegacao_t direcao);
        void gerar_descricao_scn();
        
        void atualizar_tela();       
        void limpar_tela();

        void adicionar_objeto_na_tree_view(const char* nome);

        void selecionar_objeto(const char* nome);
        void editar_objeto_translacao(double x, double y);
        void editar_objeto_escalonamento(double x, double y);
        void editar_objeto_rotacao_entorno_centro_mundo(double grau);
        void editar_objeto_rotacao_entorno_centro_objeto(double grau);
        void editar_objeto_rotacao_entorno_centro_ponto(double grau, double x, double y);

    private:

        DisplayFile *_display_file;
        Window *_window;
        Viewport *_viewport;

        std::vector<Coordenada> *_coordenada_poligono;       

        GtkListStore * _list_store;
        size_t _objeto_selecionado;
};

void Controlador::adicionar_ponto(const char* nome, double x, double y) {
    auto obj = new Ponto(nome, Coordenada(x,y));
    _display_file->adicionar_objeto(*obj);

    atualizar_tela();
    adicionar_objeto_na_tree_view(obj->nome().c_str());

}

void Controlador::adicionar_reta(const char* nome, double x1, double y1, double x2, double y2) {
    auto reta = new Reta(nome, Coordenada(x1,y1), Coordenada(x2,y2));
    _display_file->adicionar_objeto(*reta);

    atualizar_tela();
    adicionar_objeto_na_tree_view(reta->nome().c_str());

}

void Controlador::adicionar_poligono(operacao_poligono_t operacao, const char* nome, double x, double y) {
    Poligono* poligono;
    Objeto* obj;

    switch (operacao) {
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

            adicionar_objeto_na_tree_view(obj->nome().c_str());
            atualizar_tela();

            break;

        case CANCELAR:
            _coordenada_poligono->clear();
            break;
    }
}

void Controlador::zoom(direcao_zoom_t direcao) {
    _window->zoom(direcao, 10);
    atualizar_tela();
}

void Controlador::navagacao(direcao_navegacao_t direcao) {
    _window->navagacao(direcao, 10);
    atualizar_tela();
}

void Controlador::gerar_descricao_scn() {

    auto wc = _window->centro();
    auto altura = (2/_window->altura());
    auto largura = (2/_window->largura());
    auto d = Transformacao();
    auto s = Transformacao();
    d.translacao(-wc.valor(Coordenada::x), -wc.valor(Coordenada::y));
    s.escalonamento_natural(0, 0, largura, altura);

    d *= s;

    for(size_t i = 0; i < _display_file->tamanho(); i++) {
        Objeto& obj = _display_file->objeto(i);
        obj.reset_scn();
        obj.aplicar_tranformacao_scn(d);
    }
}


void Controlador::atualizar_tela() {
    limpar_tela();

    gerar_descricao_scn();

    for(size_t i = 0; i < _display_file->tamanho(); i++) {
        auto obj = _display_file->objeto(i);
        _viewport->desenhar(obj);
    }
}

void Controlador::limpar_tela() {
    _viewport->limpar_tela();
}

void Controlador::selecionar_objeto(const char* nome) {
    for(size_t i = 0; i < _display_file->tamanho(); i++) {
        auto obj = _display_file->objeto(i).nome();
        if (obj.compare(nome) == 0) {
            _objeto_selecionado = i;
            break;
        }
    }
}

void Controlador::editar_objeto_translacao(double Dx, double Dy) {

    auto obj = _display_file->objeto(_objeto_selecionado);
    auto t = Transformacao();
    t.translacao(Dx,Dy);
    
    obj.aplicar_tranformacao(t);
    atualizar_tela();
}

void Controlador::editar_objeto_escalonamento(double Sx, double Sy) {

    auto obj = _display_file->objeto(_objeto_selecionado);
    auto c = obj.centro();
    auto t = Transformacao();

    t.escalonamento_natural(c.valor(Coordenada::x), c.valor(Coordenada::y),Sx, Sy);
    obj.aplicar_tranformacao(t);

    atualizar_tela();
}

void Controlador::editar_objeto_rotacao_entorno_centro_objeto(double grau) {
    auto obj = _display_file->objeto(_objeto_selecionado);
    auto c = obj.centro();

    editar_objeto_rotacao_entorno_centro_ponto(grau, c.valor(Coordenada::x), c.valor(Coordenada::y));
}

void Controlador::editar_objeto_rotacao_entorno_centro_mundo(double grau) {
    editar_objeto_rotacao_entorno_centro_ponto(grau, 0, 0);
}

void Controlador::editar_objeto_rotacao_entorno_centro_ponto(double grau, double Dx, double Dy) {
    auto obj = _display_file->objeto(_objeto_selecionado);
    auto t = Transformacao();
    t.rotacao_em_torno_ponto(grau, Dx, Dy);
    obj.aplicar_tranformacao(t);
    atualizar_tela();
}

void Controlador::adicionar_objeto_na_tree_view(const char* nome) {
  GtkTreeIter iter;

  gtk_list_store_append(_list_store, &iter);
  gtk_list_store_set(_list_store, &iter, 0, nome, -1);
}

#endif
