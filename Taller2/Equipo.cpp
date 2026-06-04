#include "Equipo.h"
#include <iostream>
using namespace std;

Equipo::Equipo() : tam(0) {
    datos = (Pokemon*) malloc(sizeof(Pokemon));
}

Equipo::~Equipo() {
    for (int i = 0; i < tam; i++) {
        datos[i].~Pokemon();
    }
    free(datos);
    datos = nullptr;
}

/**
 * malloc/realloc:
 *  1.Se reserva nuevo bloque con malloc del tamaño necesario.
 *  2.Se mueven/copian los objetos existentes al nuevo bloque con placement new.
 *  3.Se destruyen los objetos del bloque antiguo.
 *  4.Se libera el bloque antiguo con free.
 *  5.Se construye el nuevo Pokemon al final con placement new.
 */
bool Equipo::agregar(const Pokemon& p) {
    if (tam >= MaxEquipo) {
        return false;
    }

    int nuevoTam = tam + 1;
    Pokemon* nuevo = (Pokemon*) malloc(nuevoTam * sizeof(Pokemon));
    if (nuevo == nullptr) {
        cerr << "Error: fallo al agregar Pokemon." << endl;
        return false;
    }

    for (int i = 0; i < tam; i++) {
        new (&nuevo[i]) Pokemon(datos[i]);
        datos[i].~Pokemon(); 
    }

    free(datos);
    datos = nuevo;

    new (&datos[tam]) Pokemon(p);
    tam++;
    return true;
}

bool Equipo::eliminar(int id) {
    int posicion = -1;
    for (int i = 0; i < tam; i++) {
        if (datos[i].getId() == id) {
            posicion = i;
            break;
        }
    }
    if (posicion == -1) return false; 

    if (tam == 1) {
        datos[0].~Pokemon();
        free(datos);
        datos = (Pokemon*) malloc(sizeof(Pokemon));
        tam = 0;
        return true;
    }

    int nuevoTam = tam - 1;
    Pokemon* nuevo = (Pokemon*) malloc(nuevoTam * sizeof(Pokemon));
    if (nuevo == nullptr) {
        cerr << "Error: fallo al eliminar Pokemon." << endl;
        return false;
    }

    int j = 0;
    for (int i = 0; i < tam; i++) {
        if (i != posicion) {
            new (&nuevo[j]) Pokemon(datos[i]);
            j++;
        }
        datos[i].~Pokemon();
    }

    free(datos);
    datos = nuevo;
    tam = nuevoTam;
    return true;
}

Pokemon* Equipo::buscar(int id) {
    for (int i = 0; i < tam; i++) {
        if (datos[i].getId() == id) {
            return &datos[i];
        }
    }
    return nullptr;
}

bool Equipo::estaVacio() const { return tam == 0; }
bool Equipo::estaLleno() const { return tam >= MaxEquipo; }
int  Equipo::getTam()    const { return tam; }

const Pokemon& Equipo::getDato(int indice) const {
    return datos[indice];
}

void Equipo::mostrarTodos() const {
    if (tam == 0) {
        cout << "  (El equipo esta vacio)" << endl;
        return;
    }
    for (int i = 0; i < tam; i++) {
        cout << "--------------------------------------------" << endl;
        datos[i].mostrar();
    }
    cout << "--------------------------------------------" << endl;
}
