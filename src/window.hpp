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
            _altura(altura), _largura(largura) {}

        void navagacao(direcao_navegacao_t direcao, double escalar);

        void zoom(direcao_zoom_t direcao, double escalar);

        void rotacao(double grau_x, double grau_y, double grau_z);

        Coordenada centro();

        double altura();

        double largura();

        void reset_angulo();

        Transformacao projecao_paralela();

    private:

        Coordenada _centro;
        double _angulo_x{0};
        double _angulo_y{0};
        double _angulo_z{0};
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

void Window::rotacao(double grau_x, double grau_y, double grau_z) {
    _angulo_x += grau_x;
    if (_angulo_x >= 360) {
        _angulo_x -= 360;
    }

    _angulo_y += grau_y;
    if (_angulo_y >= 360) {
        _angulo_y -= 360;
    }

    _angulo_z += grau_z;
    if (_angulo_z >= 360) {
        _angulo_z -= 360;
    }
}

Coordenada Window::centro() {
    return _centro;
}

void Window::reset_angulo() {
    _angulo_x = 0;
    _angulo_y = 0;
    _angulo_z = 0;
}

Transformacao Window::projecao_paralela() {
    /* Passo 1,2,3.1 Projecao paralela*/
    auto wc = centro();
    auto altura = (2/_altura);
    auto largura = (2/_largura);
    auto profundidade = (4/(altura+largura));

    int x = Coordenada::x;
    int y = Coordenada::y;
    int z = Coordenada::z;

    /* Translade VRP para origem */
    auto to = Transformacao::translacao(-wc.valor(x), -wc.valor(y), -wc.valor(z));

    /* Rotacione o Mundo em torno do eixo X e Y  */
    auto rx = Transformacao::rotacao_eixo_x(-_angulo_x);
    auto ry = Transformacao::rotacao_eixo_y(-_angulo_y);

    /* Matriz de Escalonamento para Coordenada normalizada*/
    auto cn = Transformacao::escalonamento(altura, largura, profundidade);

    return to * rx * ry * cn;
}

#endif