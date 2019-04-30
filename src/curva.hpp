#ifndef CURVA_HPP
#define CURVA_HPP

#include <string>
#include "objeto.hpp"
#include<vector>

class Curva : public Objeto 
{
    public:
        Curva(const std::string nome):Objeto(nome, tipo_t::CURVA_BEZIER) {}

        void adicionar_ponto_controle(double x, double y) {
            _pontos_controle.push_back(Coordenada(x,y));
        }

        void gerar_curva() {}

    coordenadas_t _pontos_controle;
};

#endif