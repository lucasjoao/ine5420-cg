#ifndef COORDENADA_HPP
#define COORDENADA_HPP

#include <vector>

#include "transformacao.hpp"

class Coordenada {

    public:
        static const size_t x = 0;
        static const size_t y = 1;
        static const size_t z = 2;
        static const size_t dimensao = 3;

    public:

        Coordenada(double x, double y);

        double valor(size_t posicao);

        void alterar(double v, size_t posicao);

        void carregar(double v[3]);

        void carregar(Coordenada &c);

        void operator*=(const Transformacao &t);

        double tamanho();

        double angulo();

        static double coeficiente_angular(Coordenada &c1, Coordenada &c2);

    private:

        double* _coordenada;

};

Coordenada::Coordenada(double x, double y) {
    _coordenada = new double[Coordenada::dimensao];
    _coordenada[Coordenada::x] = x;
    _coordenada[Coordenada::y] = y;
    _coordenada[Coordenada::z] = 1;
}

void Coordenada::alterar(double v, size_t posicao) {
    _coordenada[posicao] = v;
}

double Coordenada::valor(size_t posicao) {
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

#endif
