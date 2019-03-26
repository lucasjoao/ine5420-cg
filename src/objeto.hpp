#ifndef OBJETO
#define OBJETO

#include <string>
#include "coordenada.hpp"

typedef std::vector<Coordenada> coordenadas_t;

enum tipo_t {
    PONTO, RETA, POLIGONO
};

class Objeto {

    public:

        Objeto(const std::string& nome, tipo_t tipo);

        ~Objeto();

        std::string nome() const;

        tipo_t tipo() const;

        coordenadas_t * coordenadas();

        bool operator==(const Objeto& obj) const;

        bool operator!=(const Objeto& obj) const;


    protected:
        std::string _nome;
        tipo_t _tipo;
        std::vector<Coordenada> *_coordenadas;
};

Objeto::Objeto(const std::string& nome, tipo_t tipo) {
    _nome = std::string(nome);
    _tipo = tipo;
    _coordenadas = new coordenadas_t();
}

Objeto::~Objeto() {
    delete _coordenadas;
}

std::string Objeto::nome() const {
    return _nome;
}

tipo_t Objeto::tipo() const {
    return _tipo;
}

coordenadas_t * Objeto::coordenadas() {
    return _coordenadas;
}

bool Objeto::operator==(const Objeto& obj) const {
    return (_nome.compare(obj._nome) == 0) && _tipo == obj._tipo; 
}

bool Objeto::operator!=(const Objeto& obj) const {
    return !operator==(obj);
}

#endif