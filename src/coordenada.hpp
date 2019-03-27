#ifndef COORDENADA
#define COORDENADA

#include <vector>

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

#endif