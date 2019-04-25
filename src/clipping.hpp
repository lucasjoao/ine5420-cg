#ifndef CLIPPING_HPP
#define CLIPPING_HPP

#include "objeto.hpp"
#include <iostream>

typedef unsigned int codigo_t;

class Clipping {

        const size_t x = Coordenada::x;
        const size_t y = Coordenada::y;

        const codigo_t _esquerda = 1;
        const codigo_t _direita = 2;
        const codigo_t _baixo = 4;
        const codigo_t _cima = 8;
    public:
        Coordenada w_min = Coordenada(-1,-1);
        Coordenada w_max = Coordenada(1, 1);

    public:

        void clipping(Objeto& obj, int alg);

    private:

        void ponto(Objeto& obj);

        /* Cohen-Sutherland Clipping */
        void reta_alg0(Objeto& obj);

        void reta_alg1(Objeto& obj);

        void poligono(Objeto& obj);

        codigo_t codigo_ponto(Coordenada &c);

        Coordenada calcular_intersecao(Coordenada &p, codigo_t c, double m);

};

void Clipping::clipping(Objeto& obj, int alg) {

    switch (obj.tipo())
        {
        case tipo_t::PONTO:
            ponto(obj);
            break;

        case tipo_t::RETA:
            if (alg)
                reta_alg1(obj);
            else
                reta_alg0(obj);
            break;

        case tipo_t::POLIGONO:
            poligono(obj);
            break;

        default:
            break;
        }
}

void Clipping::ponto(Objeto& obj) {
    auto c = obj.coordenada_scn(0);
    if (w_min.valor(x) <= c.valor(x) && c.valor(x) <= w_max.valor(x)) {
        if (w_min.valor(y) <= c.valor(y) && c.valor(y) <= w_max.valor(y)) {
            obj._visivel = true;
            return;
        }
    }
    obj._visivel = false;
}

void Clipping::reta_alg0(Objeto& obj) {
    auto p1 = obj.coordenada_scn(0);
    auto p2 = obj.coordenada_scn(1);

    auto c1 = codigo_ponto(p1);
    auto c2 = codigo_ponto(p2);

    if (c1 & c2) {
        obj._visivel = false;
    } else if ( (c1 | c2) == 0) {
        obj._visivel = true;
    } else {
        auto m = Coordenada::coeficiente_anguluar(p1, p2);

        auto novo_p1 = calcular_intersecao(p1, c1, m);
        auto novo_p2 = calcular_intersecao(p2, c2, m);

        c1 = codigo_ponto(novo_p1);
        c2 = codigo_ponto(novo_p2);

        if (c1)
            novo_p1 = calcular_intersecao(novo_p1, c1, m);
        if (c2)
            novo_p2 = calcular_intersecao(novo_p2, c2, m);

        c1 = codigo_ponto(novo_p1);
        c2 = codigo_ponto(novo_p2);

        if (c1 || c2) {
            obj._visivel = false;
        } else {
            obj._visivel = true;
            obj._coordenadas_scn[0] = novo_p1;
            obj._coordenadas_scn[1] = novo_p2;
        }
    }
}

Coordenada Clipping::calcular_intersecao(Coordenada &p, codigo_t c, double coef_angular) {

    auto novo_x = p.valor(x);
    auto novo_y = p.valor(y);

    if (c & _esquerda) {
        novo_y = coef_angular*(w_min.valor(x) - p.valor(x)) + p.valor(y);       
        novo_x = w_min.valor(x);
    } else if (c &_direita) {
        novo_y = coef_angular*(w_max.valor(x) - p.valor(x)) + p.valor(y);
        novo_x = w_max.valor(x);
    } else if (c & _cima) {
        novo_x = (1/coef_angular)*(w_max.valor(y) - p.valor(y)) + p.valor(x);
        novo_y = w_max.valor(y);
    } else if (c & _baixo) {
        novo_x = (1/coef_angular)*(w_min.valor(y) - p.valor(y)) + p.valor(x);
        novo_y = w_min.valor(y);
    }
    return Coordenada(novo_x, novo_y);
}

codigo_t Clipping::codigo_ponto(Coordenada &c) {
    codigo_t codigo = 0;

    if (c.valor(y) > w_max.valor(y))
        codigo += _cima;
    else
        if (c.valor(y) < w_min.valor(y))
            codigo += _baixo; 

    if (c.valor(x) > w_max.valor(x))
        codigo += _direita;
    else
        if (c.valor(x) < w_min.valor(x))
            codigo += _esquerda; 

    return codigo;
}

void Clipping::reta_alg1(Objeto& obj) {std::cout << "clipping::reta_alg1" << std::endl;}

void Clipping::poligono(Objeto& obj) {std::cout << "clipping::poligono" << std::endl;}

#endif