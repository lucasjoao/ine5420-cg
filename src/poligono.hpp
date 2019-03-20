#ifndef OBJETO_POLIGONO
#define OBJETO_POLIGONO


#include <string>
#include "objeto.hpp"
#include<vector>

class Poligono : public Objeto {
    
    public:
        Poligono(const std::string& nome): Objeto(nome, "Poligono") {}

        void adicionar_ponto(double x, double y) {
            _coordenadas->push_back(Coordenada(x,y));
        }

};

#endif