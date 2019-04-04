#ifndef TRANSFORMACOES
#define TRANSFORMACOES

#include<cmath>
#include<iostream>
namespace transformacoes {

    const double identidade [3][3] = {{1,0,0}, {0,1,0}, {0,0,1}};

    void matriz_identidade(double matriz[3][3]);

    void matriz_translacao(double matriz[3][3] , double Dx, double Dy);
    void matriz_escalonamento(double matriz[3][3] , double Sx, double Sy);
    void matriz_rotacao(double matriz[3][3] , double grau);
    
    void multiplicacao_matrizes(double resposta[3][3], double A[3][3], double B[3][3]);
    void multiplicacao_vetor_matriz(double resposta[3], double V[3], double A[3][3]);

}

void transformacoes::matriz_identidade(double matriz[3][3]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            matriz[i][j] = identidade[i][j];
        }
    }
}

void transformacoes::matriz_translacao(double matriz[3][3] , double Dx, double Dy) {
    transformacoes::matriz_identidade(matriz);
    matriz[2][0] = Dx;
    matriz[2][1] = Dy;
}

void transformacoes::matriz_escalonamento(double matriz[3][3] , double Sx, double Sy) {
    transformacoes::matriz_identidade(matriz);
    matriz[0][0] = Sx;
    matriz[1][1] = Sy;
}

void transformacoes::matriz_rotacao(double matriz[3][3] , double grau) {
    grau = grau * M_PI/180;

    transformacoes::matriz_identidade(matriz);
    matriz[0][0] = cos(grau);
    matriz[0][1] = -sin(grau);
    matriz[1][0] = sin(grau);
    matriz[1][1] = cos(grau);
}

void transformacoes::multiplicacao_matrizes(double resposta[3][3], double A[3][3], double B[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            resposta[i][j] = A[i][0]*B[0][j] + A[i][1]*B[1][j] + A[i][2]*B[2][j]; 
        }
    }
}

void transformacoes::multiplicacao_vetor_matriz(double resposta[3], double V[3], double A[3][3]) {
    for (int i = 0; i < 3; i++) {
            resposta[i] = V[0]*A[0][i] + V[1]*A[1][i] + V[2]*A[2][i]; 
    }
}

#endif