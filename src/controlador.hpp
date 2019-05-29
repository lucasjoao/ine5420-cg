#ifndef CONTROLADOR_HPP
#define CONTROLADOR_HPP

#include "coordenada.hpp"
#include "objeto.hpp"
#include "ponto.hpp"
#include "reta.hpp"
#include "poligono.hpp"
#include "curva.hpp"
#include "display_file.hpp"
#include "window.hpp"
#include "viewport.hpp"
#include "transformacao.hpp"
#include "descritor_objeto.hpp"
#include "clipping.hpp"
#include <iostream>
#include <fstream>

#include <gtk/gtk.h>

enum operacao_obj_t {
    NOVO, ADICIONAR_PONTO, CONCLUIR, CANCELAR
};

class Controlador {

    public:

        Controlador(DisplayFile* display_file, Window *window, Viewport *viewport, GtkListStore* list_store):
            _list_store(list_store),
            _display_file(display_file), _window(window), _viewport(viewport),
            _coordenada_obj(new std::vector<Coordenada>()),
            _descritor_objeto(new DescritorObjeto()) {}

        void adicionar_ponto(const std::string nome,double x, double y, double z);
        void adicionar_reta(const std::string nome, double x1, double y1, double x2, double y2);
        void adicionar_poligono(operacao_obj_t operacao, const std::string nome, double x, double y);

        void adicionar_curva_novo();
        void adicionar_curva_adicionar_ponto(double x, double y);
        void adicionar_curva_concluir(tipo_t tipo_curva, std::string nome);
        void adicionar_curva_cancelar();

        void zoom(direcao_zoom_t direca);
        void navagacao(direcao_navegacao_t direcao);
        void gerar_descricao_scn();
        void clipping();

        void redesenhar();
        void atualizar_tela();
        void limpar_tela();

        void rotacao_window(double grau);

        void adicionar_objeto_na_tree_view(const char* nome);

        void selecionar_objeto(const char* nome);
        void editar_objeto_translacao(double x, double y);
        void editar_objeto_escalonamento(double x, double y);
        void editar_objeto_rotacao_entorno_centro_mundo(double grau);
        void editar_objeto_rotacao_entorno_centro_objeto(double grau);
        void editar_objeto_rotacao_entorno_centro_ponto(double grau, double x, double y);

        void selecionar_algoritmo_clipping_reta(int alg);

        void poligono_preenchido(bool valor);
        bool get_poligono_preenchido();

        size_t numero_pontos_obj();

        void salvar_arquivo(std::string filename);
        void carregar_arquivo(std::string filename);

    private:

        DisplayFile *_display_file;
        Window *_window;
        Viewport *_viewport;

        std::vector<Coordenada> *_coordenada_obj;
        size_t _numero_pontos_obj;

        GtkListStore * _list_store;
        size_t _objeto_selecionado;

        DescritorObjeto *_descritor_objeto;

        int _alg_clipping_reta;

        bool _poligono_preenchido;

        void criar_obj_do_arquivo(std::vector<std::string> obj);
};

size_t Controlador::numero_pontos_obj() {
    return _numero_pontos_obj;
}

void Controlador::rotacao_window(double grau) {
    _window->rotacao(grau);
    atualizar_tela();
}

void Controlador::adicionar_ponto(const std::string nome, double x, double y, double z) {
    Objeto obj = Ponto(nome, Coordenada(x,y,z));
    _display_file->adicionar_objeto(obj);

    atualizar_tela();
    adicionar_objeto_na_tree_view(obj.nome().c_str());
}

void Controlador::adicionar_reta(const std::string nome, double x1, double y1, double x2, double y2) {
    auto reta = new Reta(nome, Coordenada(x1,y1), Coordenada(x2,y2));
    _display_file->adicionar_objeto(*reta);

    atualizar_tela();
    adicionar_objeto_na_tree_view(reta->nome().c_str());
}

void Controlador::adicionar_poligono(operacao_obj_t operacao, const std::string nome, double x, double y) {
    Poligono* poligono;
    Objeto* obj;

    switch (operacao) {
        case NOVO:
            if (!_coordenada_obj->empty())
                _coordenada_obj->empty();

            break;

        case ADICIONAR_PONTO:
            _coordenada_obj->push_back(Coordenada(x,y));
            break;

        case CONCLUIR:
            if (_coordenada_obj->size() < 1)
                return;

            poligono = new Poligono(nome, _poligono_preenchido);
            for(size_t i = 0; i < _coordenada_obj->size(); i++) {
                poligono->adicionar_coordenada(_coordenada_obj->at(i));
            }

            _coordenada_obj->clear();
            _display_file->adicionar_objeto(*poligono);
            obj = poligono;

            adicionar_objeto_na_tree_view(obj->nome().c_str());
            atualizar_tela();

            break;

        case CANCELAR:
            _coordenada_obj->clear();
            break;
    }
}

void Controlador::adicionar_curva_novo() {
    if (!_coordenada_obj->empty())
        _coordenada_obj->empty();
        _numero_pontos_obj = 0;
}

void Controlador::adicionar_curva_adicionar_ponto(double x, double y) {
    _coordenada_obj->push_back(Coordenada(x,y));
    _numero_pontos_obj++;
}

void Controlador::adicionar_curva_concluir(tipo_t tipo_curva, std::string nome) {
    Objeto* obj;
    bool gerou;
    if (tipo_curva == tipo_t::CURVA_BEZIER) {
        CurvaBezier* curva_bezier = new CurvaBezier(nome);
        for(size_t i = 0; i < _coordenada_obj->size(); i++) {
            curva_bezier->adicionar_ponto_controle(_coordenada_obj->at(i));
        }

        gerou = curva_bezier->gerar_curva(100);
        if (!gerou)
            return;

        obj = curva_bezier;

    } else {

        CurvaBSpline* curva_bspline = new CurvaBSpline(nome);
        for(size_t i = 0; i < _coordenada_obj->size(); i++) {
            curva_bspline->adicionar_ponto_controle(_coordenada_obj->at(i));
        }
        gerou = curva_bspline->gerar_curva(100);
        if (!gerou)
            return;

        obj = curva_bspline;
    }
    _coordenada_obj->clear();
    _display_file->adicionar_objeto(*obj);
    adicionar_objeto_na_tree_view(obj->nome().c_str());
    atualizar_tela();
}

void Controlador::adicionar_curva_cancelar(){
    _numero_pontos_obj = 0;
    _coordenada_obj->clear();
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
    auto r = Transformacao();
    auto angulo = _window->angulo();

    d.translacao(-wc.valor(Coordenada::x), -wc.valor(Coordenada::y));
    r.rotacao(-angulo);
    s.escalonamento_natural(0, 0, largura, altura);

    d *= r;
    d *= s;

    for(size_t i = 0; i < _display_file->tamanho(); i++) {
        Objeto& obj = _display_file->objeto(i);
        obj.reset_scn();
        obj.aplicar_tranformacao_scn(d);
    }
}

void Controlador::redesenhar() {
    _viewport->limpar_tela();
    _viewport->desenhar_viewport();

    for(size_t i = 0; i < _display_file->tamanho(); i++) {
        auto obj = _display_file->objeto(i);

        if (obj.visivel())
            _viewport->desenhar(obj);
    }
}

void Controlador::clipping() {
    auto c = Clipping();
    for(size_t i = 0; i < _display_file->tamanho(); i++) {
        Objeto& obj = _display_file->objeto(i);
        c.clipping(obj, _alg_clipping_reta);
    }
}

void Controlador::atualizar_tela() {
    gerar_descricao_scn();
    clipping();
    redesenhar();
}

void Controlador::limpar_tela() {
    _viewport->limpar_tela();
    gtk_list_store_clear(_list_store);
    _display_file->limpar();
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

void Controlador::selecionar_algoritmo_clipping_reta(int alg) {
    _alg_clipping_reta = alg;
    atualizar_tela();
}

void Controlador::poligono_preenchido(bool valor) {
    _poligono_preenchido = valor;
}

bool Controlador::get_poligono_preenchido() {
    return _poligono_preenchido;
}

void Controlador::salvar_arquivo(std::string filename) {
    std::ofstream file;

    file.open(filename);

    for (size_t i = 0; i < _display_file->tamanho(); i++) {
        auto obj = _display_file->objeto(i);
        file << _descritor_objeto->descreve_objeto(obj);
    }

    file.close();
}

void Controlador::carregar_arquivo(std::string filename) {
    limpar_tela();

    std::ifstream file;
    std::string line;

    file.open(filename);

    // obj ira possuir todas as linhas do arquivo que representam um objeto
    std::vector<std::string> obj;
    while (getline(file, line)) {
        obj.push_back(line);
        if (line.find(_descritor_objeto->end_of_object) != std::string::npos) {
            criar_obj_do_arquivo(obj);
            obj.clear();
        }
    }

    file.close();
}

// vector obj
// posicao 0 possui o seu tipo
// posicao 1 possui o nome do objeto
// posicao 2 ate antepenultima possui os vertices
// penultima posicao indica se eh preenchido (1) ou nao (0) - so para poligonos
// ultima posicao possui um indicador de fim do objeto
// ver DescritorObjeto::descreve_objeto
void Controlador::criar_obj_do_arquivo(std::vector<std::string> obj) {

    // if (obj.at(0) == _descritor_objeto->ponto) {

    //     auto point = _descritor_objeto->split_line_in_vector(obj.at(2));
    //     adicionar_ponto(obj.at(1), point.at(0), point.at(1));

    // } else if (obj.at(0) == _descritor_objeto->reta) {

    //     auto point0 = _descritor_objeto->split_line_in_vector(obj.at(2));
    //     auto point1 = _descritor_objeto->split_line_in_vector(obj.at(3));
    //     adicionar_reta(obj.at(1), point0.at(0), point0.at(1),
    //                    point1.at(0), point1.at(1));

    // } else if (obj.at(0) == _descritor_objeto->poligono) {

    //     adicionar_poligono(NOVO, "", 0, 0);

    //     // lembrar que:
    //     // primeiro vertice sempre iniciara na posicao 2 do vetor obj
    //     // e terminara na antepenultima posicao do vetor obj
    //     for (size_t i = 2; i < obj.size() - 2; i++) {
    //         auto point = _descritor_objeto->split_line_in_vector(obj.at(i));
    //         adicionar_poligono(ADICIONAR_PONTO, "", point.at(0), point.at(1));
    //     }
    //     poligono_preenchido(obj.at(obj.size() - 2) == "1");

    //     adicionar_poligono(CONCLUIR, obj.at(1), 0, 0);

    // }
}

#endif
