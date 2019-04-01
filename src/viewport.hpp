#ifndef OBJETO_VIEWPORT
#define OBJETO_VIEWPORT

#include <string>
#include "objeto.hpp"
#include "coordenada.hpp"
#include "window.hpp"
#include <gtk/gtk.h>
#include <iostream>

class Viewport {

    public:

        Viewport(cairo_surface_t *surface, double minX, double minY, double maxX, double maxY) :
            _surface(surface), _minima(Coordenada(minX, minY)), _maxima(Coordenada(maxX, maxY)) {
                iniciar();
            }

        void desenhar(Objeto &obj, Window &window);

        void desenhar_ponto(Objeto &obj, Window &window);

        void desenhar_reta(Objeto &obj, Window &window);

        void desenhar_poligono(Objeto &obj, Window &window);

        void limpar_tela();

        Coordenada transformada_viewport(Coordenada &coordenada, Window &window);

    private:

        void iniciar();

        cairo_surface_t *_surface;
        Coordenada _minima;
        Coordenada _maxima;
};

void Viewport::iniciar() {

}

void Viewport::desenhar(Objeto &obj, Window &window) {
    auto tipo = obj.tipo();

    switch (tipo)
    {
        case tipo_t::PONTO:
            desenhar_ponto(obj, window);
            break;

        case tipo_t::RETA:
            desenhar_reta(obj, window);
            break;

        case tipo_t::POLIGONO:
            desenhar_poligono(obj, window);
            break;

        default:
            break;
    }
}


void Viewport::desenhar_ponto(Objeto &obj, Window &window) {
	auto c_obj = obj.coordenada(0);
    auto c = transformada_viewport(c_obj, window);

    cairo_t *cairo;
    cairo = cairo_create(_surface);
    cairo_set_source_rgb(cairo,0,0,0);
    cairo_set_line_width(cairo, 1);

    cairo_move_to(cairo, c.valor(0), c.valor(1));
	cairo_arc(cairo, c.valor(0), c.valor(1), 1.0, 0.0, (2*G_PI) );
	cairo_fill(cairo);
}

void Viewport::desenhar_reta(Objeto &obj, Window &window) {

    auto c_obj = obj.coordenada(0);
    auto c1 = transformada_viewport(c_obj, window);

    c_obj = obj.coordenada(1);
    auto c2 = transformada_viewport(c_obj, window);

    cairo_t *cairo;
    cairo = cairo_create(_surface);
    cairo_set_source_rgb(cairo,0,0,0);
    cairo_set_line_width(cairo, 1);

    cairo_move_to(cairo, c1.valor(0) , c1.valor(1));
    cairo_line_to(cairo, c2.valor(0), c2.valor(1));

    cairo_stroke(cairo);
}

void Viewport::desenhar_poligono(Objeto &obj, Window &window) {

    cairo_t *cairo;
    cairo = cairo_create(_surface);
    cairo_set_source_rgb(cairo,0,0,0);
    cairo_set_line_width(cairo, 1);


    for(size_t i = 1; i < obj.quantidade_coordenada(); i++) {
        auto c_anterior = obj.coordenada(i-1);
        auto c1 = transformada_viewport(c_anterior, window);

        auto c_atual = obj.coordenada(i);
        auto c2 = transformada_viewport(c_atual, window);

        cairo_move_to(cairo, c1.valor(0) , c1.valor(1));
        cairo_line_to(cairo, c2.valor(0), c2.valor(1));
        cairo_stroke(cairo);
    }

    auto c_anterior = obj.coordenada(obj.quantidade_coordenada()-1);
    auto c1 = transformada_viewport(c_anterior, window);

    auto c_atual = obj.coordenada(0);
    auto c2 = transformada_viewport(c_atual, window);

    cairo_move_to(cairo, c1.valor(0) , c1.valor(1));
    cairo_line_to(cairo, c2.valor(0), c2.valor(1));

    cairo_stroke(cairo);

}

Coordenada Viewport::transformada_viewport(Coordenada &c, Window &window) {

    auto w_min = window.coordenada(Window::minima);
    auto w_max = window.coordenada(Window::maxima);

    auto x = 0;
    auto y = 1;

    double xvp =  ((c.valor(x) - w_min.valor(x))/(w_max.valor(x) - w_min.valor(x)))*(_maxima.valor(x)- _minima.valor(x));

    double yvp = ( 1 - ((c.valor(y) - w_min.valor(x))/ (w_max.valor(y) - w_min.valor(y)))  ) * (_maxima.valor(y) - _minima.valor(y));

    return Coordenada(xvp, yvp);
}

void Viewport::limpar_tela() {
  cairo_t *cr;

  cr = cairo_create (_surface);

  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_paint (cr);

  cairo_destroy (cr);
}



#endif
