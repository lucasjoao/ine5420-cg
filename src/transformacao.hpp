#ifndef TRANSFORMACAO_HPP
#define TRANSFORMACAO_HPP

#include<cmath>

#include "coordenada.hpp"

class Transformacao {
    const double _identidade [4][4] = {{1,0,0,0}, 
                                       {0,1,0,0}, 
                                       {0,0,1,0},
                                       {0,0,0,1}};
    public:
        Transformacao(): _matriz{{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}} {}

        Transformacao(double M[4][4]) {
            carragar(M);
        }

        void identidade();

        void carragar(const double matriz[4][4]);

        static Transformacao translacao(double Dx, double Dy, double Dz);

        static Transformacao escalonamento(double Sx, double Sy, double Sz);

        static Transformacao escalonamento_natural(double Cx, double Cy, double Cz, double Sx, double Sy, double Sz);

        static Transformacao rotacao_eixo_x(double grau);

        static Transformacao rotacao_eixo_y(double grau);

        static Transformacao rotacao_eixo_z(double grau);

        static Transformacao rotacao_em_torno_ponto(double grau, double Dx, double Dy);

        double valor(size_t i, size_t j) const;

        void operator*=(const Transformacao &t);

        Transformacao operator*(const Transformacao &t);

    private:
        double _matriz[4][4];

};

Transformacao Transformacao::escalonamento_natural(double Cx, double Cy, double Cz, double Sx, double Sy, double Sz) {
    auto s = Transformacao::escalonamento(Sx, Sy, Sz);
    auto d1 = Transformacao::translacao(-Cx, -Cy, -Cz);
    auto d2 = Transformacao::translacao(Cx, Cy, Cz);

    return d1 * s * d2;
}

void Transformacao::identidade() {
    carragar(_identidade);
}

void Transformacao::carragar(const double matriz[4][4]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            _matriz[i][j] = matriz[i][j];
        }
    }
}

Transformacao Transformacao::translacao(double Dx, double Dy, double Dz) {
    Transformacao t;
    t._matriz[3][0] = Dx;
    t._matriz[3][1] = Dy;
    t._matriz[3][2] = Dz;
    return t;
}

Transformacao Transformacao::escalonamento(double Sx, double Sy, double Sz) {
    Transformacao t;
    t._matriz[0][0] = Sx;
    t._matriz[1][1] = Sy;
    t._matriz[2][2] = Sz;
    return t;
}

Transformacao Transformacao::rotacao_eixo_x(double grau) {
    grau = grau * M_PI/180;

    Transformacao t;

    t._matriz[1][1] = cos(grau);
    t._matriz[1][2] = sin(grau);
    t._matriz[2][2] = -sin(grau);
    t._matriz[2][2] = cos(grau);
    return t;
}

Transformacao Transformacao::rotacao_eixo_y(double grau) {
    grau = grau * M_PI/180;

    Transformacao t;

    t._matriz[0][0] = cos(grau);
    t._matriz[0][2] = -sin(grau);
    t._matriz[2][0] = sin(grau);
    t._matriz[2][2] = cos(grau);
    return t;
}

Transformacao Transformacao::rotacao_eixo_z(double grau) {
    grau = grau * M_PI/180;

    Transformacao t;

    t._matriz[0][0] = cos(grau);
    t._matriz[0][1] = sin(grau);
    t._matriz[1][0] = -sin(grau);
    t._matriz[1][1] = cos(grau);
    return t;
}

Transformacao Transformacao::rotacao_em_torno_ponto(double grau, double Dx, double Dy) {
    // auto r = Transformacao();
    // auto d = Transformacao();

    // r.rotacao_eixo_z(grau);
    // d.translacao(Dx, Dy, 1);
    // translacao(-Dx, -Dy, 1);

    // *this *= r;
    // *this *= d;
    return Transformacao();
}


double Transformacao::valor(size_t i, size_t j) const {
    return _matriz[i][j];
}

void Transformacao::operator*=(const Transformacao &t) {
    double R[4][4];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            R[i][j] = _matriz[i][0]*t._matriz[0][j] + _matriz[i][1]*t._matriz[1][j] + _matriz[i][2]*t._matriz[2][j] + _matriz[i][3]*t._matriz[3][j]; 
        }
    }
    carragar(R);
}

Transformacao Transformacao::operator*(const Transformacao &t) {
    double R[4][4];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            R[i][j] = _matriz[i][0]*t._matriz[0][j] + _matriz[i][1]*t._matriz[1][j] + _matriz[i][2]*t._matriz[2][j] + _matriz[i][3]*t._matriz[3][j]; 
        }
    }

    return Transformacao(R);
}


#endif