#ifndef CURVA_HPP
#define CURVA_HPP

#include <string>
#include "objeto.hpp"
#include<vector>
#include <iostream>

class CurvaBezier : public Objeto 
{
    public:
        CurvaBezier(const std::string nome):Objeto(nome, tipo_t::CURVA_BEZIER) {}

        /* 3n + 1 pontos precisam ser adicionados, n > 0*/
        void adicionar_ponto_controle(Coordenada c) {
            _pontos_controle.push_back(c);
        }

        bool gerar_curva(double passos) {
            if (_pontos_controle.size() < 3 || ((_pontos_controle.size() - 1) % 3))
                return false;

            double t = 0;
            double distancia_entre_pontos = 1/passos;

            double cx, cy, cz, bx, by, bz, ax, ay, az;
            int x = Coordenada::x;
            int y = Coordenada::y;
            int z = Coordenada::z;

            for (int i = 0; i+1 < _pontos_controle.size(); i+=3) {
                Coordenada p1 = _pontos_controle[i];
                Coordenada p2 = _pontos_controle[i+1];
                Coordenada p3 = _pontos_controle[i+2];
                Coordenada p4 = _pontos_controle[i+3];

                cx = 3*(p2.valor(x)- p1.valor(x));
                cy = 3*(p2.valor(y)- p1.valor(y));
                cz = 3*(p2.valor(z)- p1.valor(z));
                bx = 3*(p3.valor(x)- p2.valor(x)) - cx;
                by = 3*(p3.valor(y)- p2.valor(y)) - cy;
                bz = 3*(p3.valor(z)- p2.valor(z)) - cz;
                ax = (p4.valor(x) - p1.valor(x)) - (cx+bx);
                ay = (p4.valor(y) - p1.valor(y)) - (cy+by);
                az = (p4.valor(z) - p1.valor(z)) - (cz+bz);

                double novo_x, novo_y, novo_z;
                for (size_t j = 0; j < passos+1; j++) {
                    novo_x = p1.valor(x) + t*(cx+t*(bx+t*ax));
                    novo_y = p1.valor(y) + t*(cy+t*(by+t*ay));
                    novo_z = p1.valor(z) + t*(cz+t*(bz+t*az));
                    _coordenadas.push_back(Coordenada(novo_x, novo_y, novo_z));
                    t = t+distancia_entre_pontos;
                }
            }
            return true;
        }

    private:
        coordenadas_t _pontos_controle;
};


class CurvaBSpline : public Objeto 
{
    public:
        CurvaBSpline(const std::string nome):Objeto(nome, tipo_t::CURVA_BSPLINE) {}

        void adicionar_ponto_controle(Coordenada c) {
            _pontos_controle.push_back(c);
        }

        bool gerar_curva(double passos) {
            if (_pontos_controle.size() < 4 )
                return false;

            double distancia_entre_pontos = 1/passos;
            double t = distancia_entre_pontos;
            double t2 = t*t;
            double t3 = t*t2;

            for (size_t i = 0; i < _pontos_controle.size()-3; i++)
            {
                Coordenada p1 = _pontos_controle[i];
                Coordenada p2 = _pontos_controle[i+1];
                Coordenada p3 = _pontos_controle[i+2];
                Coordenada p4 = _pontos_controle[i+3];

                double ax,bx,cx,dx;
                double ay,by,cy,dy;
                double az,bz,cz,dz;

                double delta_x3, delta_x2, delta_x1;
                double delta_y3, delta_y2, delta_y1;
                double delta_z3, delta_z2, delta_z1;

                int x = Coordenada::x;
                int y = Coordenada::y;
                int z = Coordenada::z;

                ax = -(1.0/6.0) * p1.valor(x) + 0.5 * p2.valor(x) -0.5 * p3.valor(x) +(1.0/6.0) * p4.valor(x);
				bx =  0.5 * p1.valor(x) -p2.valor(x) +0.5 * p3.valor(x);
				cx = -0.5 * p1.valor(x) +0.5 * p3.valor(x);
				dx =  (1.0/6.0) * p1.valor(x) +(2.0/3.0) * p2.valor(x) +(1.0/6.0) * p3.valor(x);

                ay = -(1.0/6.0) * p1.valor(y) + 0.5 * p2.valor(y) -0.5 * p3.valor(y) +(1.0/6.0) * p4.valor(y);
				by =  0.5 * p1.valor(y) -p2.valor(y) +0.5 * p3.valor(y);
				cy = -0.5 * p1.valor(y) +0.5 * p3.valor(y);
				dy =  (1.0/6.0) * p1.valor(y) +(2.0/3.0) * p2.valor(y) +(1.0/6.0) * p3.valor(y);

                az = -(1.0/6.0) * p1.valor(z) + 0.5 * p2.valor(z) -0.5 * p3.valor(z) +(1.0/6.0) * p4.valor(z);
				bz =  0.5 * p1.valor(z) -p2.valor(z) +0.5 * p3.valor(z);
				cz = -0.5 * p1.valor(z) +0.5 * p3.valor(z);
				dz =  (1.0/6.0) * p1.valor(z) +(2.0/3.0) * p2.valor(z) +(1.0/6.0) * p3.valor(z);


				delta_x1  = ax * t3 + bx * t2 + cx * t;
				delta_x2 = ax * (6 * t3) + bx * (2 * t2);
				delta_x3 = ax * (6 * t3);

				delta_y1 = ay * t3 + by * t2 + cy * t;
				delta_y2 = ay * (6 * t3) + by * (2 * t2);
				delta_y3 = ay * (6 * t3);

				delta_z1 = az * t3 + bz * t2 + cz * t;
				delta_z2 = az * (6 * t3) + bz * (2 * t2);
				delta_z3 = az * (6 * t3);

                double novo_x, novo_y, novo_z;

                novo_x = dx; 
                novo_y = dy;
                novo_z = dz;
                _coordenadas.push_back(Coordenada(novo_x, novo_y, novo_z));

                for (size_t j = 0; j < passos+1; j++) {
                	novo_x += delta_x1;
					delta_x1 += delta_x2;
					delta_x2 += delta_x3;

					novo_y += delta_y1;
					delta_y1 += delta_y2;
					delta_y2 += delta_y3;

					novo_z += delta_z1;
					delta_z1 += delta_z2;
					delta_z2 += delta_z3;

                    _coordenadas.push_back(Coordenada(novo_x, novo_y, novo_z));
                }
            }
            return true;
        }
    private:
        coordenadas_t _pontos_controle;
};

#endif