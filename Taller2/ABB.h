#ifndef ABB_H
#define ABB_H
#include "Pokemon.h"

/**
 * @struct NodoABB
 * Nodo interno del Árbol Binario de Búsqueda.
 *
 * Cada nodo almacena un Pokémon y punteros a sus subárboles
 * izquierdo (IDs menores) y derecho (IDs mayores).
 */
    struct NodoABB {
    Pokemon   dato;
    NodoABB* izq;
    NodoABB* der;

    /**
     * Constructor del nodo.
     * @param p Pokémon que se almacena en el nodo.
     */
    NodoABB(const Pokemon& p) : dato(p), izq(nullptr), der(nullptr) {}
};

class ABB {
private:
    NodoABB* raiz;
    NodoABB* insertarRec(NodoABB* nodo, const Pokemon& p);
    NodoABB* eliminarRec(NodoABB* nodo, int id);
    NodoABB* minimoNodo(NodoABB* nodo) const;
    void buscarSucesorRec(NodoABB* nodo, int idBuscado, NodoABB*& sucesor) const;
    void destruirRec(NodoABB* nodo);
    int contarRec(NodoABB* nodo) const;

public:
    ABB();
    ~ABB();
    void insertar(const Pokemon& p);
    Pokemon* buscar(int id);
    void eliminar(int id);
    Pokemon* buscarSucesor(int idBuscado);
    bool estaVacio() const;
    int cantidad() const;
};

#endif 