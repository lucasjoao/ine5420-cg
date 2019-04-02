#ifndef OBJETO_WINDOWS
#define OBJETO_WINDOWS

#include <string>
#include "objeto.hpp"

class Window: public Objeto {
    public:
        static const size_t minima = 0;
        static const size_t maxima = 1;

    public:

        Window(Coordenada minima, Coordenada maxima) : Objeto("Window", tipo_t::WINDOW) {
            _coordenadas.push_back(minima);
            _coordenadas.push_back(maxima);
        }

};

#endif