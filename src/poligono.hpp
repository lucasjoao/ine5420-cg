#ifndef OBJETO_POLIGONO_HPP
#define OBJETO_POLIGONO_HPP


#include <string>
#include "objeto.hpp"
#include<vector>

class Poligono : public Objeto {

    public:
        Poligono(const std::string nome, bool preenchido):
            Objeto(nome, tipo_t::POLIGONO) {
                set_preenchido(preenchido);
            }

        void adicionar_coordenada(double x, double y) {
            _coordenadas.push_back(Coordenada(x,y));
        }
};

#endif
