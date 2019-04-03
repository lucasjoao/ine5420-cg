#ifndef OBJETO_WINDOWS
#define OBJETO_WINDOWS

#include <string>
#include "objeto.hpp"

enum direcao_zoom_t {
    IN, OUT
};

enum direcao_navegacao_t {
    UP, DOWN, LEFT, RIGHT
};

class Window: public Objeto {
    public:
        static const size_t minima = 0;
        static const size_t maxima = 1;

    public:

        Window(Coordenada minima, Coordenada maxima) : Objeto("Window", tipo_t::WINDOW) {
            _coordenadas.push_back(minima);
            _coordenadas.push_back(maxima);
        }

        void navagacao(direcao_navegacao_t direcao, double escalar);

};

void Window::navagacao(direcao_navegacao_t direcao, double escalar) {
    Coordenada &c_min = _coordenadas[Window::minima];
    Coordenada &c_max = _coordenadas[Window::maxima];
    auto x = Coordenada::x;
    auto y = Coordenada::y;

    switch (direcao)
    {
        case UP:
            c_min.alterar(c_min.valor(y)-escalar, y);
            c_max.alterar(c_max.valor(y)-escalar, y);
            break;

        case DOWN:
            c_min.alterar(c_min.valor(y)+escalar, y);
            c_max.alterar(c_max.valor(y)+escalar, y);
            break;

        case RIGHT:
            c_min.alterar(c_min.valor(x)-escalar, x);
            c_max.alterar(c_max.valor(x)-escalar, x);
            break;

        case LEFT:
            c_min.alterar(c_min.valor(x)+escalar, x);
            c_max.alterar(c_max.valor(x)+escalar, x);
            break;

        default:
            break;

    }

}

#endif