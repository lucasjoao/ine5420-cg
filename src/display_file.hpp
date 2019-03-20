#ifndef CONTROLADOR
#define CONTROLADOR

#include <string>
#include "objeto.hpp"
#include "windows.hpp"
#include "viewport.hpp"


class DisplayFile {
    public:

        DisplayFile() : _lista_objetos(new std::vector<Objeto>()), _viewport(new Viewport(0,0, 800, 600)) {}


        void adicionar_objeto(const Objeto& obj)  {
            _lista_objetos->push_back(obj);

            atualizar_viewport();
        }

        void atualizar_viewport() {
            for (auto i = _lista_objetos->begin(); i != _lista_objetos->end(); i++) {
                auto coord = *i->get_coordenadas();
                auto tipo = *i->get_tipo();

                _viewport->desenhar(tipo, coord);
            }
        }

    private:
        std::vector<Objeto> *_lista_objetos;
        Viewport *_viewport;

};

#endif