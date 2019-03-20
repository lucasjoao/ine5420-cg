#ifndef OBJETO_RETA
#define OBJETO_RETA

#include <string>
#include "objeto.hpp"

class Reta : public Objeto {
    
    public:
        Reta(const std::string& nome, Coordenada c1, Coordenada c2): Objeto(nome, "Reta") {
            _coordenadas->push_back(c1);
            _coordenadas->push_back(c2);
        };

};

#endif