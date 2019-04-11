#ifndef OBJETO
#define OBJETO

#include <string>
#include "coordenada.hpp"
#include "transformacoes.hpp"

typedef std::vector<Coordenada> coordenadas_t;

enum tipo_t {
    PONTO, RETA, POLIGONO
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
        
        Coordenada coordenada_scn(size_t posicao);

        Coordenada centro();
        
        Coordenada centro_scn();

        size_t tamanho();

        size_t tamanho_scn();

        void normalizar(double matriz[3][3], double altura, double largura);

        bool operator==(const Objeto& obj) const;

        bool operator!=(const Objeto& obj) const;

    protected:
        std::string _nome;
        tipo_t _tipo;
        std::vector<Coordenada> _coordenadas;
        std::vector<Coordenada> _coordenadas_scn;
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

        default:
            break;
    }

    _nome = apelido;
    _tipo = tipo;
    _coordenadas = coordenadas_t();
    _coordenadas_scn = coordenadas_t();
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

Coordenada Objeto::coordenada_scn(size_t posicao) {
    return _coordenadas_scn.at(posicao);
}

Coordenada Objeto::centro() {
    double x = 0;
    double y = 0;
    size_t tamanho = this->tamanho();

    for(size_t i = 0; i < tamanho; i++) {
        x += _coordenadas[i].valor(Coordenada::x);
        y += _coordenadas[i].valor(Coordenada::y);
    }

    x = x/tamanho;
    y = y/tamanho;
    return Coordenada(x,y);  
}

Coordenada Objeto::centro_scn() {
    double x = 0;
    double y = 0;
    size_t tamanho = this->tamanho_scn();

    for(size_t i = 0; i < tamanho; i++) {
        x += _coordenadas_scn[i].valor(Coordenada::x);
        y += _coordenadas_scn[i].valor(Coordenada::y);
    }

    x = x/tamanho;
    y = y/tamanho;
    return Coordenada(x,y);  
}

size_t Objeto::tamanho() {
    return _coordenadas.size();
}

size_t Objeto::tamanho_scn() {
    return _coordenadas_scn.size();
}

void Objeto::normalizar(double matriz[3][3], double altura, double largura) {
    double T[3][3];
    double S[3][3];
    double V[3];
    double R[3];

    _coordenadas_scn.clear();

    transformacoes::matriz_escalonamento_natural(
        S, centro().valor(Coordenada::x), centro().valor(Coordenada::y), largura, altura
    );
    transformacoes::multiplicacao_matrizes(T, matriz, S);

    for(size_t i = 0; i < tamanho(); i++) {
        auto c = coordenada(i);
        V[0] = c.valor(0);
        V[1] = c.valor(1);
        V[2] = c.valor(2);

        transformacoes::multiplicacao_vetor_matriz(R,V,T);

        _coordenadas_scn.push_back(Coordenada(R[0], R[1]));
    }
}


bool Objeto::operator==(const Objeto& obj) const {
    return (_nome.compare(obj._nome) == 0) && _tipo == obj._tipo; 
}

bool Objeto::operator!=(const Objeto& obj) const {
    return !operator==(obj);
}

#endif