#ifndef CLIPPING_HPP
#define CLIPPING_HPP

#include "objeto.hpp"
#include <iostream>
#include <algorithm>

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
        void clipping(Objeto& obj, int alg);

    private:

        void ponto(Objeto& obj);

        /* Cohen-Sutherland Clipping */
        void reta_alg0(Objeto& obj);

        /* Liang-Barsky Line Clipping */
        void reta_alg1(Objeto& obj);

        /* Weiler-Atherton Clipping */
        void poligono(Objeto& obj);

        void curva(Objeto& obj);

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

        case tipo_t::CURVA_BEZIER:
            curva(obj);
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

void Clipping::reta_alg1(Objeto& obj) {
    auto c1 = obj.coordenada_scn(0);
    auto c2 = obj.coordenada_scn(1);

    double dx = c2.valor(x) - c1.valor(x);
    double dy = c2.valor(y) - c1.valor(y);

    double p1 = -dx;
    double p2 = dx;
    double p3 = -dy;
    double p4 = dy;

    double q1 = c1.valor(x) - w_min.valor(x);
    double q2 = w_max.valor(x) - c1.valor(x);
    double q3 = c1.valor(y) - w_min.valor(y);
    double q4 = w_max.valor(y) - c1.valor(y);

    double r1 = q1/p1;
    double r2 = q2/p2;
    double r3 = q3/p3;
    double r4 = q4/p4;

    double z1 = 0;
    double z2 = 1;

    if (p1) {
        if (p1 < 0) {
            z1 = std::max(z1, r1);
        } else {
            z2 = std::min(z2, r1);
        }
    }

    if (p2) {
        if (p2 < 0) {
                z1 = std::max(z1, r2);
            } else {
                z2 = std::min(z2, r2);
            }
    }

    if (p3) {
        if (p3 < 0) {
            z1 = std::max(z1, r3);
        } else {
            z2 = std::min(z2, r3);
        }
    }

    if (p4) {
        if (p4 < 0) {
            z1 = std::max(z1, r4);
        } else {
            z2 = std::min(z2, r4);
        }
    }

    double novo_x, novo_y;
    if (z1 > z2) {
        obj._visivel = false;
    } else {
        obj._visivel = true;
        if (z1 > 0) {
            novo_x = c1.valor(x) + z1 * dx;
            novo_y = c1.valor(y) + z1 * dy;
            obj._coordenadas_scn[0] = Coordenada(novo_x, novo_y);
        }
        if (z2 < 1) {
            novo_x = c1.valor(x) + z2 * dx;
            novo_y = c1.valor(y) + z2 * dy;
            obj._coordenadas_scn[1] = Coordenada(novo_x, novo_y);
        }
    }
}

void Clipping::poligono(Objeto& obj) {
    // poligono de recorte é a região do recorte
    // poligono objeto eh o poligono a ser recortado

    // TODO:
    // conversar aldo se precisa ser esse

    // problemas:
    // nao tenho a lista em sentido horario, tenho no sentido da insercao
    // usar qual tipo de coordenada?

    for (auto coord : obj._coordenadas) {
        std::cout << coord.valor(0);
        std::cout << coord.valor(1);
    }

    // TESTES
    // exemplos slides
    // não clipa porque nada aparece
    // não clipa porque não tem intersecção

}

void Clipping::curva(Objeto& obj)
{
    auto list_coord = obj._coordenadas_scn;
    obj._coordenadas_scn.clear();
    for (int i = 0; i < list_coord.size(); i++) {
        auto c = list_coord[i];

        if (w_min.valor(x) <= c.valor(x) && c.valor(x) <= w_max.valor(x)) {
            if (w_min.valor(y) <= c.valor(y) && c.valor(y) <= w_max.valor(y)) {
                obj._coordenadas_scn.push_back(c);
            }
        }
    }
    if (obj._coordenadas_scn.size()) {
        obj._visivel = true;
    } else {
        obj._visivel = false;
    }
}


#endif
