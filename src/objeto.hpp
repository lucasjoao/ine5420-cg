#ifndef OBJETO
#define OBJETO

#include <string>
#include "coordenada.hpp"

typedef std::vector<Coordenada> coordenadas_t;

enum tipo_t {
    PONTO, RETA, POLIGONO, WINDOW
};

class Objeto {
    public:
        static size_t _id;

    public:

        Objeto(const std::string& nome, tipo_t tipo);

        ~Objeto();

        const std::string& nome() const;

        tipo_t tipo() const;

        Coordenada coordenada(size_t posicao);

        size_t quantidade_coordenada();

        bool operator==(const Objeto& obj) const;

        bool operator!=(const Objeto& obj) const;

    protected:
        std::string _nome;
        tipo_t _tipo;
        std::vector<Coordenada> _coordenadas;
};

size_t Objeto::_id = 0;

Objeto::Objeto(const std::string& nome, tipo_t tipo) {
    _id++;

    auto apelido = std::to_string(_id) + "-";
    switch (tipo)
    {
        case PONTO:
            apelido += "PONTO";
            break;

        case RETA:
            apelido += "RETA";
            break;

        case POLIGONO:
            apelido += "POLIGONO";
            break;

        case WINDOW:
            apelido += "WINDOW";
            break;

        default:
            break;
    }


    _nome = apelido;
    _tipo = tipo;
    _coordenadas = coordenadas_t();
}

Objeto::~Objeto() {}

const std::string& Objeto::nome() const {
    return _nome;
}

tipo_t Objeto::tipo() const {
    return _tipo;
}

Coordenada Objeto::coordenada(size_t posicao) {
    return _coordenadas.at(posicao);
}

size_t Objeto::quantidade_coordenada() {
    return _coordenadas.size();
}


bool Objeto::operator==(const Objeto& obj) const {
    return (_nome.compare(obj._nome) == 0) && _tipo == obj._tipo; 
}

bool Objeto::operator!=(const Objeto& obj) const {
    return !operator==(obj);
}

#endif