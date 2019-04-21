#ifndef CLIPPING_HPP
#define CLIPPING_HPP

#include "objeto.hpp"
#include <iostream>

class Clipping {

    public:

        void clipping(Objeto& obj, int alg);

    private:

        void ponto(Objeto& obj);

        void reta_alg0(Objeto& obj);

        void reta_alg1(Objeto& obj);

        void poligono(Objeto& obj);

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

void Clipping::ponto(Objeto& obj) {std::cout << "clipping::ponto" << std::endl;}

void Clipping::reta_alg0(Objeto& obj) {std::cout << "clipping::reta_alg0" << std::endl;}

void Clipping::reta_alg1(Objeto& obj) {std::cout << "clipping::reta_alg1" << std::endl;}

void Clipping::poligono(Objeto& obj) {std::cout << "clipping::poligono" << std::endl;}

#endif