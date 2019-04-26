#ifndef OBJETO_POLIGONO_HPP
#define OBJETO_POLIGONO_HPP


#include <string>
#include "objeto.hpp"
#include<vector>

class Poligono : public Objeto {

    private:

        bool _preenchido;

    public:
        // TODO: adicionar no construtor o preenchido
        // TODO: ver algum jeito de mudar o minimo possivel no controlador
        // TODO: ver como faz para preencher
        Poligono(const std::string nome): Objeto(nome, tipo_t::POLIGONO) {}

        void adicionar_coordenada(double x, double y) {
            _coordenadas.push_back(Coordenada(x,y));
        }

        bool preenchido() {
            return _preenchido;
        }

};

#endif
