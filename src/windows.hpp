#ifndef OBJETO_WINDOWS
#define OBJETO_WINDOWS

#include <string>
#include "coordenada.hpp"

class Windows {

    public:

        Windows(double minX, double minY, double maxX, double maxY) : 
            _min(Coordenada(minX, minY)), _max(Coordenada(maxX, maxY)) {}

        void movimentar(double valor) {
            _min.mover(valor);
            _max.mover(valor);
        }

        void zoom(double valor) {
            _min.mover(-valor);
            _max.mover(valor);
        }

        Coordenada get_min() {
            return _min;
        }

        Coordenada get_max() {
            return _max;
        }

    private:

    Coordenada _min;
    Coordenada _max;

};

#endif