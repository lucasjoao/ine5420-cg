#ifndef COORDENADA_HPP
#define COORDENADA_HPP

#include <vector>

#include "transformacao.hpp"

class Coordenada {

    public:
        static const size_t x = 0;
        static const size_t y = 1;
        static const size_t z = 2;
        static const size_t w = 3;
        static const size_t dimensao = 4;

        Coordenada();

        Coordenada(double x, double y);

        Coordenada(double x, double y, double z);

        double valor(size_t posicao) const;

        void alterar(double v, size_t posicao);

        void carregar(double v[3]);

        void carregar(Coordenada &c);

        static double coeficiente_angular(Coordenada &c1, Coordenada &c2);

        void operator*=(const Transformacao &t);

        bool operator==(const Coordenada &coordenada) const;

        void set_artificial(const bool artificial);

        bool is_artificial() const;

    private:

        double* _coordenada;

        /* utilizado no algoritmo de clipping de poligono */
        bool _artificial;

};

Coordenada::Coordenada() {}

Coordenada::Coordenada(double x, double y) {
    _coordenada = new double[Coordenada::dimensao];
    _coordenada[Coordenada::x] = x;
    _coordenada[Coordenada::y] = y;
    _coordenada[Coordenada::z] = 1;
    _coordenada[Coordenada::w] = 1;
    _artificial = false;
}

Coordenada::Coordenada(double x, double y, double z) {
    _coordenada = new double[Coordenada::dimensao];
    _coordenada[Coordenada::x] = x;
    _coordenada[Coordenada::y] = y;
    _coordenada[Coordenada::z] = z;
    _coordenada[Coordenada::w] = 1;
    _artificial = false;
}

void Coordenada::alterar(double v, size_t posicao) {
    _coordenada[posicao] = v;
}

double Coordenada::valor(size_t posicao) const {
    return _coordenada[posicao];
}

void Coordenada::carregar(double v[3]) {
    _coordenada[0] = v[0];
    _coordenada[1] = v[1];
    _coordenada[2] = v[2];
}

void Coordenada::carregar(Coordenada &c) {
    _coordenada[0] = c.valor(0);
    _coordenada[1] = c.valor(1);
    _coordenada[2] = c.valor(2);
    _coordenada[3] = c.valor(3);
}

double Coordenada::coeficiente_angular(Coordenada &c1, Coordenada &c2) {
    return (c2.valor(y) - c1.valor(y))/(c2.valor(x) - c1.valor(x));
}

void Coordenada::operator*=(const Transformacao &t) {
    double R[3];

    for (int i = 0; i < 3; i++) {
            R[i] = valor(0)*t.valor(0,i) + valor(1)*t.valor(1,i) + valor(2)*t.valor(2,i);
    }

    carregar(R);
}

bool Coordenada::operator==(const Coordenada &coordenada) const {
    return (_coordenada[Coordenada::x] == coordenada.valor(Coordenada::x)) &&
           (_coordenada[Coordenada::y] == coordenada.valor(Coordenada::y));
}

void Coordenada::set_artificial(const bool artificial) {
    _artificial = artificial;
}

bool Coordenada::is_artificial() const {
    return _artificial;
}

#endif
