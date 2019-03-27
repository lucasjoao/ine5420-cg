#ifndef CONTROLADOR
#define CONTROLADOR

#include <string>
#include "objeto.hpp"
#include "window.hpp"
#include "viewport.hpp"


class DisplayFile {

    public:

        DisplayFile(Viewport* viewport, Window *window) : _lista_objetos(new std::vector<Objeto>()), _viewport(viewport),
        _window(window) {}

        void adicionar_objeto(const Objeto& obj)  {
            _lista_objetos->push_back(obj);

            atualizar_viewport();
        }

        void atualizar_viewport() {
            // cairo_surface_t *surface;

            // for (auto i = _lista_objetos->begin(); i != _lista_objetos->end(); i++) {
            //     auto coord = *i->coordenadas();
            //     auto tipo = i->tipo();

            //     _viewport->desenhar(*i, _window, surface);
            // }
        }

    private:
        std::vector<Objeto> *_lista_objetos;
        Viewport *_viewport;
        Window *_window;

};

#endif