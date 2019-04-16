#ifndef OBJETO_PONTO_HPP
#define OBJETO_PONTO_HPP

#include "objeto.hpp"


class Ponto : public Objeto {

    public:
        Ponto(const std::string nome,  Coordenada c): Objeto(nome, tipo_t::PONTO) {
            _coordenadas.push_back(c);
        };


};

#endif
