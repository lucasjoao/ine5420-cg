#ifndef OBJETO_PONTO
#define OBJETO_PONTO

#include "objeto.hpp"


class Ponto : public Objeto {
    
    public:
        Ponto(const std::string& nome,  double x, double y): Objeto(nome, "Ponto") {
            _coordenadas->push_back(Coordenada(x,y));
        };


};

#endif