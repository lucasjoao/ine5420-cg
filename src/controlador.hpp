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

enum direcao_zoom_t {
    IN, OUT
};

enum direcao_navegacao_t {
    UP, DOWN, LEFT, RIGHT
};

class Controlador {


    public:


        Controlador(DisplayFile* display_file, Window *window, Viewport *viewport):
            _display_file(display_file), _window(window), _viewport(viewport) {}

        void adicionar_ponto(const char* nome,double x, double y);
        void adicionar_reta(const char* nome, double x1, double y1, double x2, double y2);
        void adicionar_poligono(const char* nome);
        
        void zoom(direcao_zoom_t direcao, double escalar);

        void navagacao(direcao_navegacao_t direcao, double escalar);

        void atualizar_tela();       
        void limpar_tela();
        
    private:

        DisplayFile *_display_file;
        Window *_window;
        Viewport *_viewport;

};

void Controlador::adicionar_ponto(const char* nome, double x, double y) {
    auto obj = new Ponto(nome, Coordenada(x,y));
    _display_file->adicionar_objeto(obj);

    _viewport->desenhar_ponto(*obj, *_window);
}

void Controlador::adicionar_reta(const char* nome, double x1, double y1, double x2, double y2) {
    auto reta = new Reta(nome, Coordenada(x1,y1), Coordenada(x2,y2));
    _display_file->adicionar_objeto(reta);
    _viewport->desenhar(*reta, *_window);
}

void Controlador::adicionar_poligono(const char* nome) {
    // IMPLEMENTAR
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

void Controlador::navagacao(direcao_navegacao_t direcao, double escalar) {
    // IMPLEMENTAR

    switch (direcao)
    {
        case UP:
            break;

        case DOWN:
            break;

        case LEFT:
            break;

        case RIGHT:
            break;

        default:
            break;

    }
}

void Controlador::atualizar_tela() {
    limpar_tela();

    for(size_t i = 0; i < _display_file->tamanho(); i++) {
        auto obj = _display_file->objeto(i);
        _viewport->desenhar(*obj, *_window);
    }
}

void Controlador::limpar_tela() {
    _viewport->limpar_tela();
}

#endif