#ifndef COORDENADA
#define COORDENADA

#include <vector>

class Coordenada {

    public:
        Coordenada(double x, double y) {
            _coordenada = new double[2];
            _coordenada[0] = x;
            _coordenada[1] = y;
        }

        void mover(double x) {
            _coordenada[0] += x;
            _coordenada[1] += x;
        }

        double* get_coordenada() {
            return _coordenada;
        }
    private:

        double* _coordenada;

};

#endif