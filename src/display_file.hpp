#ifndef DISPLAY_FILE_HPP
#define DISPLAY_FILE_HPP

#include <string>
#include "objeto.hpp"
#include "window.hpp"
#include "viewport.hpp"

class DisplayFile {

    public:

        DisplayFile() : _lista_objetos(new std::vector<Objeto>()) {}

        void adicionar_objeto(Objeto &obj);

        Objeto& objeto(size_t posicao);

        void remover_objeto(const std::string& nome);

        size_t tamanho();

        void limpar();

    private:
        std::vector<Objeto> *_lista_objetos;

};

void DisplayFile::adicionar_objeto(Objeto &obj) {
    _lista_objetos->push_back(obj);
}

Objeto& DisplayFile::objeto(size_t posicao) {
    return _lista_objetos->at(posicao);
}

void DisplayFile::remover_objeto(const std::string& nome) {
    // IMPLEMENTAR
}

size_t DisplayFile::tamanho() {
    return _lista_objetos->size();
}

void DisplayFile::limpar() {
    _lista_objetos->clear();
}

#endif
