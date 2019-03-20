#ifndef OBJETO_VIEWPORT
#define OBJETO_VIEWPORT

#include <string>
#include "objeto.hpp"
#include "windows.hpp"
#include <gtk/gtk.h>

class Viewport {

    public:

        Viewport(double minX, double minY, double maxX, double maxY) : _minX(minX), _minY(minY),
        _maxX(maxX), _maxY(maxY), _windows{new Windows(minX, minY, maxX, maxY)} {}

        void desenhar(const std::string& tipo, const std::vector<Coordenada> &coordenadas) {
            if (tipo.compare("Ponto")) {
                desenhar_ponto(coordenadas);
            } else if (tipo.compare("Reta")) {
                desenhar_reta(coordenadas);
            } else if (tipo.compare("Poligono")) {
                desenhar_poligno(coordenadas);
            }
        }

        void desenhar_ponto(const std::vector<Coordenada> &coordenadas) {

        }

        void desenhar_reta(const std::vector<Coordenada> &coordenadas) {

        }

        void desenhar_poligno(const std::vector<Coordenada> &coordenadas) {

        }

    private:

        double _minX;
        double _minY;
        double _maxX;
        double _maxY;

        Windows *_windows;

};

#endif