#ifndef ESTRUTURA_LISTA_ENCADEADA
#define ESTRUTURA_LISTA_ENCADEADA


#include <stdexcept>  // c++ exceptions
#include "Elemento.hpp"
#include <iostream>
template<typename T>
class ListaEnc {

public:

	ListaEnc();

	~ListaEnc();

	// inicio
	void adicionaNoInicio(const T& dado);

	T retiraDoInicio();

	void eliminaDoInicio();

	// posicao
	void adicionaNaPosicao(const T& dado, int pos);

	int posicao(const T& dado) const;

	T* posicaoMem(const T& dado) const;

	bool contem(const T& dado);

	T retiraDaPosicao(int pos);

	//fim
	void adiciona(const T& dado);

	T retira();

	// especifico
	T retiraEspecifico(const T& dado);

	void adicionaEmOrdem(const T& dado);

	bool listaVazia() const;

	bool igual(T dado1, T dado2);

	bool maior(T dado1, T dado2);

	bool menor(T dado1, T dado2);

	void destroiLista();

private:
	Elemento<T>* head{nullptr};
	int size{0};
};


template<typename T>
ListaEnc<T>::ListaEnc() {}

template<typename T>
ListaEnc<T>::~ListaEnc() {
	destroiLista();
}

template<typename T>
void ListaEnc<T>::adicionaNoInicio(const T& dado) {
	head = new Elemento<T>(dado, head);
	size++;
}

template<typename T>
T ListaEnc<T>::retiraDoInicio() {
	if (listaVazia()) {
		throw std::out_of_range("Lista vazia");
	}
	auto primeiro = head;
	auto dado = head->getInfo();

	head = primeiro->getProximo();
	delete primeiro;

	size--;
	return primeiro->getInfo();

}

template<typename T>
void ListaEnc<T>::eliminaDoInicio(){
	retiraDoInicio();
}

template<typename T>
void ListaEnc<T>::adicionaNaPosicao(const T& dado, int pos) {

	if (pos == 0) {
		adicionaNoInicio(dado);

	} else if (pos < 0 || pos > size){
		throw std::out_of_range("Index fora da lista");

	} else {
		auto anterior = head;

		for (int i = 1; i < pos; i++) {
			anterior = anterior->getProximo();
		}

		auto novo = new Elemento<T>(dado, anterior->getProximo());
		anterior->setProximo(novo);
		size++;
	}
	
}

template<typename T>
int ListaEnc<T>::posicao(const T& dado) const {
	if (listaVazia()) {
		throw std::out_of_range("Lista nao contem elemento");
	}
	auto elemento = head;
	int pos = 0;
	while (elemento->getInfo() != dado) {
		elemento = elemento->getProximo();
		pos++;
		if (!elemento) {
			break;
		}
	}

	return pos;
	
}

template<typename T>
T* ListaEnc<T>::posicaoMem(const T& dado) const {
	if (listaVazia()) {
		throw std::out_of_range("Lista nao contem elemento");
	}

	auto elemento = head;

	while (elemento->getInfo() != dado) {
		elemento = elemento->getProximo();
		if (!elemento) {
			throw std::out_of_range("Lista nao contem elemento");		
		}
	}

	return elemento->getInfo();
}

template<typename T>
bool ListaEnc<T>::contem(const T& dado) {
	auto elemento = head;
	while(elemento){
		if (elemento->getInfo() == dado) {
			return true;
		}
		elemento = elemento->getProximo();
	}
	return false;
}

template<typename T>
T ListaEnc<T>::retiraDaPosicao(int pos){
	if (pos == 0) {
		return retiraDoInicio();
	} else if (pos < 0 || pos > size){
		throw std::out_of_range("Posicao invalida");
	} else {
		auto anterior = head;
		for (int i = 0; i < pos; i++) {
			anterior = anterior->getProximo();
		}

		auto retira = anterior->getProximo();
		auto dado = retira->getInfo();
		anterior->setProximo(retira->getProximo());
		size--;
		delete retira;
		return dado;
	}

}

template<typename T>
void ListaEnc<T>::adiciona(const T& dado) {
	adiciona(dado);
}

template<typename T>
T ListaEnc<T>::retira() {
	if (listaVazia()) {
		throw std::out_of_range("Lista Vazia");
	}

	return retiraDaPosicao(size-1);
}

template<typename T>
T ListaEnc<T>::retiraEspecifico(const T& dado) {
	return retiraDaPosicao(dado, posicao(dado));
}

template<typename T>
void ListaEnc<T>::adicionaEmOrdem(const T& dado) { 
	if (listaVazia()) {
		adicionaNoInicio(dado);
		return;
	}

	auto elemento = head;
	int i = 0;

	while (elemento->getProximo() != nullptr && dado > elemento->getInfo()) {
		elemento = elemento->getProximo();
		i++;
	}

	adicionaNaPosicao(dado, i+1);
}


template<typename T>
bool ListaEnc<T>::listaVazia() const {
	return size == 0;
}

template<typename T>
bool ListaEnc<T>::igual(T dado1, T dado2) {
	return dado1 == dado2;
}

template<typename T>
bool ListaEnc<T>::maior(T dado1, T dado2) {
	return dado1 > dado2;
}

template<typename T>
bool ListaEnc<T>::menor(T dado1, T dado2) {
	return dado1 < dado2;
}

template<typename T>
void ListaEnc<T>::destroiLista(){
	while(!listaVazia()){
		retiraDoInicio();
	}
}

#endif