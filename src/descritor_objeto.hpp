#ifndef DESCRITOR_OBJETO_HPP
#define DESCRITOR_OBJETO_HPP

#include <string>
#include <sstream>
#include "objeto.hpp"

class DescritorObjeto {

  public:

    std::string descreve_objeto(Objeto obj);

    const std::string end_of_object = "\t\t\t FIM OBJETO \t\t\t";

    std::vector<double> split_line_in_vector(std::string line);

};

  std::string DescritorObjeto::descreve_objeto(Objeto obj) {
    std::string text;

    switch (obj.tipo()) {
      case PONTO:
        text += "pon";
        break;
      case RETA:
        text += "ret";
        break;
      case POLIGONO:
        text += "pol";
        break;
      default:
        break;
    }

    text += "\n" + obj.nome() + "\n";

    for(size_t i = 0; i < obj.tamanho(); i++) {
      auto coordenada = obj.coordenada(i);
      text += "ver ";
      text += std::to_string(coordenada.valor(0)) + " ";
      text += std::to_string(coordenada.valor(1)) + "\n";
    }

    text += end_of_object + "\n";

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

#endif
