#ifndef DESCRITOR_OBJETO_HPP
#define DESCRITOR_OBJETO_HPP

#include <string>
#include "objeto.hpp"

class DescritorObjeto {

  public:

    std::string descreve_objeto(Objeto obj);

};

  std::string DescritorObjeto::descreve_objeto(Objeto obj) {
    std::string text;

    { // primeira linha
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

      text += " " + obj.nome() + "\n";
    }

    for(size_t i = 0; i < obj.tamanho(); i++) {
      auto coordenada = obj.coordenada(i);
      text += "ver ";
      text += std::to_string(coordenada.valor(0)) + " ";
      text += std::to_string(coordenada.valor(1)) + "\n";
    }

    return text;
  }

#endif
