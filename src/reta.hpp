#ifndef OBJETO_RETA_HPP
#define OBJETO_RETA_HPP

#include <string>
#include "objeto.hpp"

class Reta : public Objeto {
    
    public:
        Reta(const std::string& nome, Coordenada c1, Coordenada c2): Objeto(nome, tipo_t::RETA) {
            _coordenadas.push_back(c1);
            _coordenadas.push_back(c2);
        };

};

#endif