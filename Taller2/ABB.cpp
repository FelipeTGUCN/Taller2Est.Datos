#include "ABB.h"
#include <iostream>
using namespace std;

ABB::ABB() : raiz(nullptr) {}

ABB::~ABB() {
    destruirRec(raiz);
    raiz = nullptr;
}

void ABB::destruirRec(NodoABB* nodo) {
    if (nodo == nullptr) return;
    destruirRec(nodo->izq);
    destruirRec(nodo->der);
    delete nodo;
}

NodoABB* ABB::insertarRec(NodoABB* nodo, const Pokemon& p) {
    if (nodo == nullptr) {
        return new NodoABB(p);
    }
    if (p.getId() < nodo->dato.getId()) {
        nodo->izq = insertarRec(nodo->izq, p);
    }
    else if (p.getId() > nodo->dato.getId()) {
        nodo->der = insertarRec(nodo->der, p);
    }
    return nodo;
}

NodoABB* ABB::minimoNodo(NodoABB* nodo) const {
    NodoABB* actual = nodo;
    while (actual != nullptr && actual->izq != nullptr) {
        actual = actual->izq;
    }
    return actual;
}

NodoABB* ABB::eliminarRec(NodoABB* nodo, int id) {
    if (nodo == nullptr) return nullptr;

    if (id < nodo->dato.getId()) {
        nodo->izq = eliminarRec(nodo->izq, id);

    }
    else if (id > nodo->dato.getId()) {
        nodo->der = eliminarRec(nodo->der, id);

    }
    else {

        if (nodo->izq == nullptr && nodo->der == nullptr) {
            delete nodo;
            return nullptr;

        }
        else if (nodo->izq == nullptr) {
            NodoABB* temp = nodo->der;
            delete nodo;
            return temp;

        }
        else if (nodo->der == nullptr) {
            NodoABB* temp = nodo->izq;
            delete nodo;
            return temp;

        }
        else {
            NodoABB* sucesor = minimoNodo(nodo->der);
            nodo->dato = sucesor->dato;
            nodo->der = eliminarRec(nodo->der, sucesor->dato.getId());
        }
    }
    return nodo;
}

void ABB::buscarSucesorRec(NodoABB* nodo, int idBuscado, NodoABB*& sucesor) const {
    if (nodo == nullptr) return;

    if (nodo->dato.getId() == idBuscado) {
        sucesor = nodo;
        return;
    }

    if (nodo->dato.getId() > idBuscado) {
        sucesor = nodo;
        buscarSucesorRec(nodo->izq, idBuscado, sucesor);
    }
    else {
        buscarSucesorRec(nodo->der, idBuscado, sucesor);
    }
}

int ABB::contarRec(NodoABB* nodo) const {
    if (nodo == nullptr) return 0;
    return 1 + contarRec(nodo->izq) + contarRec(nodo->der);
}

void ABB::insertar(const Pokemon& p) {
    raiz = insertarRec(raiz, p);
}

Pokemon* ABB::buscar(int id) {
    NodoABB* actual = raiz;
    while (actual != nullptr) {
        if (id == actual->dato.getId()) {
            return &actual->dato;
        }
        else if (id < actual->dato.getId()) {
            actual = actual->izq;
        }
        else {
            actual = actual->der;
        }
    }
    return nullptr;
}

void ABB::eliminar(int id) {
    raiz = eliminarRec(raiz, id);
}

Pokemon* ABB::buscarSucesor(int idBuscado) {
    NodoABB* sucesor = nullptr;
    buscarSucesorRec(raiz, idBuscado, sucesor);
    if (sucesor == nullptr) return nullptr;
    return &sucesor->dato;
}

bool ABB::estaVacio() const {
    return raiz == nullptr;
}

int ABB::cantidad() const {
    return contarRec(raiz);
}