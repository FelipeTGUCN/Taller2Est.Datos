#include "MaxHeap.h"
#include <iostream>
using namespace std;

MaxHeap::MaxHeap(char atributo) : tam(0), atributo(atributo) {}

int MaxHeap::valorAtributo(const Pokemon& p) const {
    return p.getStatPorCategoria(atributo);
}

void MaxHeap::subir(int indice) {
    while (indice > 0) {
        int padre = (indice - 1) / 2;
        if (valorAtributo(datos[padre]) < valorAtributo(datos[indice])) {
            Pokemon temp = datos[padre];
            datos[padre] = datos[indice];
            datos[indice] = temp;
            indice = padre;
        }
        else {
            break;
        }
    }
}

void MaxHeap::bajar(int indice) {
    while (true) {
        int hijoIzq = 2 * indice + 1;
        int hijoDer = 2 * indice + 2;
        int mayor = indice;

        if (hijoIzq < tam &&
            valorAtributo(datos[hijoIzq]) > valorAtributo(datos[mayor])) {
            mayor = hijoIzq;
        }
        if (hijoDer < tam &&
            valorAtributo(datos[hijoDer]) > valorAtributo(datos[mayor])) {
            mayor = hijoDer;
        }

        if (mayor != indice) {
            Pokemon temp = datos[mayor];
            datos[mayor] = datos[indice];
            datos[indice] = temp;
            indice = mayor;
        }
        else {
            break;
        }
    }
}

void MaxHeap::insertar(const Pokemon& p) {
    if (tam >= CAPACIDAD_HEAP) {
        cerr << "Error: capacidad máxima alcanzada." << endl;
        return;
    }
    datos[tam] = p;
    subir(tam);
    tam++;
}

Pokemon MaxHeap::extraerMax() {
    Pokemon maximo = datos[0];
    tam--;
    datos[0] = datos[tam];

    if (tam > 0) {
        bajar(0);
    }
    return maximo;
}

const Pokemon& MaxHeap::verMax() const {
    return datos[0];
}

bool MaxHeap::estaVacio() const {
    return tam == 0;
}

int MaxHeap::getTam() const {
    return tam;
}

const Pokemon& MaxHeap::getDato(int indice) const {
    return datos[indice];
}

char MaxHeap::getAtributo() const {
    return atributo;
}