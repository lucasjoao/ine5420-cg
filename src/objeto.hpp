#ifndef OBJETO
#define OBJETO

#include <string>
#include <vector>
#include "coordenada.hpp"

class Objeto {

    public:

        Objeto(const std::string& nome, const std::string& tipo):
            _nome(new std::string(nome)),
            _tipo(new std::string(tipo)),
            _coordenadas(new std::vector<Coordenada>()) {}

        ~Objeto() {
            delete _nome;
            delete _tipo;
            delete _coordenadas;
        }

        bool operator==(const Objeto& obj) {
            return _nome == obj._nome && _tipo == obj._tipo;
        }

        bool operator!=(const Objeto& obj) {
            return !(operator==(obj));
        }

        std::string *get_nome() const {
            return _nome;
        };

        std::string *get_tipo() const {
            return _tipo;
        };

        std::vector<Coordenada> *get_coordenadas() const {
            return _coordenadas;
        };

    protected:
        std::string *_nome;
        std::string *_tipo;
        std::vector<Coordenada> *_coordenadas;

};

#endif