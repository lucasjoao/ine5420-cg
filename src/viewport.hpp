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

        void desenhar(Objeto &obj);

        void desenhar_ponto(Objeto &obj);

        void desenhar_reta(Objeto &obj);

        void desenhar_poligono(Objeto &obj);

        void desenhar_curva(Objeto &obj);

        void limpar_tela();

        void desenhar_viewport();

        Coordenada transformada_viewport(Coordenada &coordenada);

    private:

        void iniciar();

        cairo_surface_t *_surface;
        Coordenada _minima;
        Coordenada _maxima;
};

void Viewport::iniciar() {
    desenhar_viewport();
}

void Viewport::desenhar(Objeto &obj) {
    auto tipo = obj.tipo();

    switch (tipo) {
        case tipo_t::PONTO:
            desenhar_ponto(obj);
            break;

        case tipo_t::RETA:
            desenhar_reta(obj);
            break;

        case tipo_t::POLIGONO:
            desenhar_poligono(obj);
            break;
        case tipo_t::CURVA_BEZIER:
        case tipo_t::CURVA_BSPLINE:
            desenhar_curva(obj);

        default:
            break;
    }
}

void Viewport::desenhar_viewport() {
    cairo_t *cairo;

    cairo = cairo_create (_surface);

    cairo_move_to(cairo, 10, 10);
    cairo_line_to(cairo, 10, 490);
    cairo_stroke(cairo);
    cairo_move_to(cairo, 10, 490);
    cairo_line_to(cairo, 490, 490);
    cairo_stroke(cairo);
    cairo_move_to(cairo, 490, 490);
    cairo_line_to(cairo, 490, 10);
    cairo_stroke(cairo);
    cairo_move_to(cairo, 490, 10);
    cairo_line_to(cairo, 10, 10);
    cairo_stroke(cairo);
}

void Viewport::desenhar_ponto(Objeto &obj) {
	auto c_obj = obj.coordenada_scn(0);
    auto c = transformada_viewport(c_obj);

    cairo_t *cairo;
    cairo = cairo_create(_surface);
    cairo_set_source_rgb(cairo,0,0,0);
    cairo_set_line_width(cairo, 1);

    cairo_move_to(cairo, c.valor(0)+10, c.valor(1)+10);
	cairo_arc(cairo, c.valor(0)+10, c.valor(1)+10, 1.0, 0.0, (2*G_PI) );
	cairo_fill(cairo);
}

void Viewport::desenhar_reta(Objeto &obj) {

    auto c_obj = obj.coordenada_scn(0);
    auto c1 = transformada_viewport(c_obj);

    c_obj = obj.coordenada_scn(1);
    auto c2 = transformada_viewport(c_obj);

    cairo_t *cairo;
    cairo = cairo_create(_surface);
    cairo_set_source_rgb(cairo,0,0,0);
    cairo_set_line_width(cairo, 1);

    cairo_move_to(cairo, c1.valor(0) + 10, c1.valor(1) + 10);
    cairo_line_to(cairo, c2.valor(0) + 10, c2.valor(1) + 10);

    cairo_stroke(cairo);
}

void Viewport::desenhar_poligono(Objeto &obj) {

    cairo_t *cairo;
    cairo = cairo_create(_surface);
    cairo_set_source_rgb(cairo,0,0,0);
    cairo_set_line_width(cairo, 1);

    auto c_inicial = obj.coordenada_scn(0);
    auto c0 = transformada_viewport(c_inicial);
    cairo_move_to(cairo, c0.valor(0) + 10, c0.valor(1) + 10);

    for (size_t i = 1; i < obj.tamanho_scn(); i++) {
        auto c_atual = obj.coordenada_scn(i);
        auto c1 = transformada_viewport(c_atual);
        cairo_line_to(cairo, c1.valor(0) + 10, c1.valor(1) + 10);
    }

    // fecha o poligono
    cairo_line_to(cairo, c0.valor(0) + 10, c0.valor(1) + 10);

    // se o poligono eh de dois pontos ou menos, entao nao desenha com fill
    if (obj.preenchido() && obj.tamanho_scn() > 2) {
        cairo_fill(cairo);
    }

    cairo_stroke(cairo);
}

void Viewport::desenhar_curva(Objeto &obj) {
    cairo_t *cairo;
    cairo = cairo_create(_surface);
    cairo_set_source_rgb(cairo,0,0,0);
    cairo_set_line_width(cairo, 1);

    auto c_inicial = obj.coordenada_scn(0);
    auto c0 = transformada_viewport(c_inicial);
    cairo_move_to(cairo, c0.valor(0) + 10, c0.valor(1) + 10);

    for (size_t i = 1; i < obj.tamanho_scn(); i++) {
        auto c_atual = obj.coordenada_scn(i);
        auto c1 = transformada_viewport(c_atual);
        cairo_line_to(cairo, c1.valor(0) + 10, c1.valor(1) + 10);
    }
    cairo_stroke(cairo);
} 

Coordenada Viewport::transformada_viewport(Coordenada &c) {

    auto w_min = Coordenada(-1,-1);
    auto w_max = Coordenada(1,1);

    auto x = 0;
    auto y = 1;

    double xvp =  ((c.valor(x) - w_min.valor(x))/(w_max.valor(x) - w_min.valor(x)))*(_maxima.valor(x)- _minima.valor(x));

    double yvp = ( 1 - ((c.valor(y) - w_min.valor(y))/ (w_max.valor(y) - w_min.valor(y)))  ) * (_maxima.valor(y) - _minima.valor(y));

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
