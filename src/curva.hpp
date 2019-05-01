#ifndef CURVA_HPP
#define CURVA_HPP

#include <string>
#include "objeto.hpp"
#include<vector>
#include <iostream>
class Curva : public Objeto 
{
    public:
        Curva(const std::string nome):Objeto(nome, tipo_t::CURVA_BEZIER) {}

        /* 3n + 1 pontos precisam ser adicionados, n > 0*/
        void adicionar_ponto_controle(double x, double y) {
            _pontos_controle.push_back(Coordenada(x,y));
        }

        void gerar_curva(double passos) {
            double t = 0;
            double distancia_entre_pontos = 1/passos;

            double cx, cy, bx, by, ax, ay;
            int x = Coordenada::x;
            int y = Coordenada::y;

            for (int i = 0; i+1 < _pontos_controle.size(); i+=3) {
                Coordenada p1 = _pontos_controle[i];
                Coordenada p2 = _pontos_controle[i+1];
                Coordenada p3 = _pontos_controle[i+2];
                Coordenada p4 = _pontos_controle[i+3];

                cx = 3*(p2.valor(x)- p1.valor(x));
                cy = 3*(p2.valor(y)- p1.valor(y));
                bx = 3*(p3.valor(x)- p2.valor(x)) - cx;
                by = 3*(p3.valor(y)- p2.valor(y)) - cy;
                ax = (p4.valor(x) - p1.valor(x)) - (cx+bx);
                ay = (p4.valor(y) - p1.valor(y)) - (cy+by);

                double novo_x, novo_y;
                for (size_t j = 0; j < passos+1; j++) {
                    novo_x = p1.valor(x) + t*(cx+t*(bx+t*ax));
                    novo_y = p1.valor(y) + t*(cy+t*(by+t*ay));
                    _coordenadas.push_back(Coordenada(novo_x, novo_y));
                    t = t+distancia_entre_pontos;
                }
            }
        }

    coordenadas_t _pontos_controle;
};

#endif