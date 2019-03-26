#ifndef OBJETO_VIEWPORT
#define OBJETO_VIEWPORT

#include <string>
#include "objeto.hpp"
#include "coordenada.hpp"
#include "windows.hpp"
#include <gtk/gtk.h>

class Viewport {

    public:

        Viewport(double minX, double minY, double maxX, double maxY) :
            _min(Coordenada(minX, minY)), _max(Coordenada(maxX, maxY)) {}

        void desenhar(Objeto obj, Windows *windows, cairo_surface_t *surface);

        void desenhar_ponto(Objeto obj, Windows *windows, cairo_surface_t *surface);

        void desenhar_reta(Objeto obj, Windows *windows, cairo_surface_t *surface);

        void desenhar_poligono(std::vector<Coordenada> *coordenadas);

        double* transformada_viewport(Coordenada *coordenada, Coordenada *windows_min, Coordenada *windows_max);

    private:

        Coordenada _min;
        Coordenada _max;
};

void Viewport::desenhar(Objeto obj, Windows *windows, cairo_surface_t *surface) {
    auto tipo = obj.tipo();

    switch (tipo)
    {
        case tipo_t::PONTO:
            /* code */
            break;

        case tipo_t::RETA:
            /* code */
            break;

        case tipo_t::POLIGONO:
            /* code */
            break;

        default:
            break;
    }
}


void Viewport::desenhar_ponto(Objeto obj, Windows *windows, cairo_surface_t *surface) {

    std::vector<Coordenada> *coordenadas = obj.coordenadas();
    auto c_obj = coordenadas->at(0);

    auto w_min = windows->get_min();
    auto w_max = windows->get_max();

    auto c = Viewport::transformada_viewport(&c_obj, &w_min, &w_max);
    auto x = 0;
    auto y = 1;


    cairo_t *cairo;
    cairo = cairo_create(surface);

    cairo_set_source_rgb(cairo,c[x],c[y],0);
    cairo_set_line_width(cairo, 1);
    cairo_fill_preserve(cairo);

    cairo_stroke(cairo);
}

void Viewport::desenhar_reta(Objeto obj, Windows *windows, cairo_surface_t *surface) {


    auto w_min = windows->get_min();
    auto w_max = windows->get_max();

    auto c_obj = obj.coordenadas()->at(0);
    auto c1 = transformada_viewport(&c_obj, &w_min, &w_max);

    c_obj = obj.coordenadas()->at(1);
    auto c2 = transformada_viewport(&c_obj, &w_min, &w_max);

    auto x = 0;
    auto y = 1;

    cairo_t *cairo;
    cairo = cairo_create(surface);
    cairo_set_source_rgb(cairo,0,0,0);
    cairo_set_line_width(cairo, 1);

    cairo_move_to(cairo, c1[x], c2[y]);
    cairo_move_to(cairo, c2[x], c2[y]);

    cairo_stroke(cairo);

}

void Viewport::desenhar_poligono(std::vector<Coordenada> *coordenadas) { }

double* Viewport::transformada_viewport(Coordenada *coordenada, Coordenada *windows_min, Coordenada *windows_max) {
    auto c = coordenada->coordenada();

    auto w_min = windows_min->coordenada();
    auto w_max = windows_max->coordenada();

    auto x = 0;
    auto y = 1;

    auto vp_max = _max.coordenada();
    auto vp_min = _min.coordenada();

    double xvp =  ((c[x] - w_min[x])/(w_max[x] - w_min[x]))*(vp_max[x]- vp_min[x]);

    double yvp = ( 1 - ((c[y] - w_min[y])/ (w_max[y] - w_min[y]))  ) * (vp_max[y] - vp_min[y]);

    return Coordenada(xvp, yvp).coordenada();
}

#endif
