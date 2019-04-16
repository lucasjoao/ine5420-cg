#ifndef TRANSFORMACAO_HPP
#define TRANSFORMACAO_HPP

#include<cmath>

#include "coordenada.hpp"

class Transformacao {
    const double _identidade [3][3] = {{1,0,0}, {0,1,0}, {0,0,1}};

    public:
        Transformacao(): _matriz{{1,0,0}, {0,1,0}, {0,0,1}} {}

        void identidade();

        void carragar(const double matriz[3][3]);

        void translacao(double Dx, double Dy);

        void escalonamento(double Sx, double Sy);

        void escalonamento_natural(double Cx, double Cy , double Sx, double Sy);

        void rotacao(double grau);

        void rotacao_em_torno_ponto(double grau, double Dx, double Dy);

        double valor(size_t i, size_t j) const;

        void operator*=(const Transformacao &t);

    private:
        double _matriz[3][3];

};

void Transformacao::escalonamento_natural(double Cx, double Cy , double Sx, double Sy) {
    auto s = Transformacao();
    auto d = Transformacao();
    s.escalonamento(Sx, Sy);
    d.translacao(Cx, Cy);

    translacao(-Cx, -Cy);

    *this *= s;
    *this *= d;
}


void Transformacao::identidade() {
    carragar(_identidade);
}

void Transformacao::carragar(const double matriz[3][3]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            _matriz[i][j] = matriz[i][j];
        }
    }
}

void Transformacao::translacao(double Dx, double Dy) {
    identidade();
    _matriz[2][0] = Dx;
    _matriz[2][1] = Dy;
}

void Transformacao::escalonamento(double Sx, double Sy) {
    identidade();
    _matriz[0][0] = Sx;
    _matriz[1][1] = Sy;
}

void Transformacao::rotacao(double grau) {
    grau = grau * M_PI/180;

    identidade();

    _matriz[0][0] = cos(grau);
    _matriz[0][1] = -sin(grau);
    _matriz[1][0] = sin(grau);
    _matriz[1][1] = cos(grau);

}

void Transformacao::rotacao_em_torno_ponto(double grau, double Dx, double Dy) {
    auto r = Transformacao();
    auto d = Transformacao();

    r.rotacao(grau);
    d.translacao(Dx, Dy);
    translacao(-Dx, -Dy);

    *this *= r;
    *this *= d;
}


double Transformacao::valor(size_t i, size_t j) const {
    return _matriz[i][j];
}

void Transformacao::operator*=(const Transformacao &t) {
    double R[3][3];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            R[i][j] = _matriz[i][0]*t._matriz[0][j] + _matriz[i][1]*t._matriz[1][j] + _matriz[i][2]*t._matriz[2][j]; 
        }
    }
    carragar(R);
}

#endif