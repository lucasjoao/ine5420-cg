#ifndef OBJETO_WINDOWS
#define OBJETO_WINDOWS

#include <string>
#include "objeto.hpp"
#include <cmath>

enum direcao_zoom_t {
    IN, OUT
};

enum direcao_navegacao_t {
    UP, DOWN, LEFT, RIGHT
};

class Window {

    public:

        Window(Coordenada origem, double altura, double largura): 
            _centro(Coordenada(origem.valor(Coordenada::x) + (largura/2), origem.valor(Coordenada::y) + (altura/2))),
            _angulo(0), _altura(altura), _largura(largura) {}

        void navagacao(direcao_navegacao_t direcao, double escalar);

        void zoom(direcao_zoom_t direcao, double escalar);

        void rotacao(double grau);

        Coordenada centro();

        double altura();

        double largura();

        double angulo();

    private:

        Coordenada _centro;
        double _angulo;
        double _altura;
        double _largura;
};

double Window::altura() {
    return _altura;
}

double Window::largura() {
    return _largura;
}

void Window::navagacao(direcao_navegacao_t direcao, double escalar) {
    auto x = Coordenada::x;
    auto y = Coordenada::y;

    switch (direcao) {
       case UP:
            _centro.alterar(_centro.valor(y)+escalar, y);
            break;

        case DOWN:
            _centro.alterar(_centro.valor(y)-escalar, y);
            break;

        case RIGHT:
            _centro.alterar(_centro.valor(x)+escalar, x);

            break;

        case LEFT:
            _centro.alterar(_centro.valor(x)-escalar, x);

            break;
     }    
}

void Window::zoom(direcao_zoom_t direcao, double escalar) {
    switch (direcao)
    {
    case IN:
        _altura -= escalar;
        _largura -= escalar;
        break;

    case OUT:
        _altura += escalar;
        _largura += escalar;
        break;

    default:
        break;
    }
}

void Window::rotacao(double grau) {
    _angulo += grau;
    if (_angulo >= 360) {
        _angulo -= 360;
    }
}

Coordenada Window::centro() {
    return _centro;
}

double Window::angulo() {
    return _angulo;
}

#endif