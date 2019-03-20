#ifndef COORDENADA
#define COORDENADA

#include <vector>

class Coordenada {

    static const int x = 0;
    static const int y = 1;

    public:
        Coordenada(double x, double y) {
            _coordenada = new std::vector<double>();
            _coordenada->push_back(x);
            _coordenada->push_back(y);
        }

        std::vector<double> *_coordenada;

};

#endif