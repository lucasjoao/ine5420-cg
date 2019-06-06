#ifndef DESCRITOR_OBJETO_HPP
#define DESCRITOR_OBJETO_HPP

#include <string>
#include <sstream>
#include "objeto.hpp"

class DescritorObjeto {

  public:

    const std::string ponto = "p";
    const std::string reta = "l";
    const std::string poligono = "f";
    const std::string vertice = "v";
    const std::string objeto = "o";

    size_t contador_de_linha = 0;

    std::string descreve_objeto(Objeto obj);

    std::vector<double> split_line_in_vector(std::string line);

    void zera_contador_de_linha();
};

  std::string DescritorObjeto::descreve_objeto(Objeto obj) {
    std::string text;

    for(size_t i = 0; i < obj.tamanho(); i++) {
      auto coordenada = obj.coordenada(i);
      text += vertice + " ";
      text += std::to_string(coordenada.valor(0)) + " ";
      text += std::to_string(coordenada.valor(1)) + " ";
      text += std::to_string(coordenada.valor(2)) + "\n";
      contador_de_linha++;
    }

    switch (obj.tipo()) {
      case PONTO:
        text += ponto;
        break;
      case RETA:
        text += reta;
        break;
      case POLIGONO:
      case CURVA_BEZIER:
      case CURVA_BSPLINE:
        text += poligono;
        break;
      default:
        break;
    }

    size_t max = contador_de_linha + 1;
    for (size_t i = max - obj.tamanho(); i < max; i++) {
      text += " " + std::to_string(i);
    }

    text += "\n" + objeto + " " + obj.nome() + "\n";

    return text;
  }

  std::vector<double> DescritorObjeto::split_line_in_vector(std::string line) {
    std::stringstream linestream(line);
    std::string tipo;
    std::string x;
    std::string y;


    linestream >> tipo >> x >> y;
    std::vector<double> result {atof(x.c_str()), atof(y.c_str())};
    return result;
  }

  void DescritorObjeto::zera_contador_de_linha() {
    contador_de_linha = 0;
  }

#endif
