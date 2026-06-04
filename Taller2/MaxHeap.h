#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "Pokemon.h"

const int CAPACIDAD_HEAP = 80;

/**
 * @class MaxHeap
 */
class MaxHeap {
private:
    Pokemon datos[CAPACIDAD_HEAP];
    int tam;
    char atributo;

    /**
     * @param p
     * @return
     */
    int valorAtributo(const Pokemon& p) const;

    /**
     * @param indice
     */
    void subir(int indice);

    /**
     * @param indice
     */
    void bajar(int indice);

public:
    /**
     * @param atributo
     */
    MaxHeap(char atributo);

    /**
     * @param p
     */
    void insertar(const Pokemon& p);

    /**
     * @return
     */
    Pokemon extraerMax();

    /**
     * @return
     */
    const Pokemon& verMax() const;

    /**
     * @return
     */
    bool estaVacio() const;

    /**
     * @return
     */
    int getTam() const;

    /**
     * @param indice
     * @return
     */
    const Pokemon& getDato(int indice) const;

    /**
     * @return
     */
    char getAtributo() const;
};

#endif