#ifndef EQUIPO_H
#define EQUIPO_H

#include "Pokemon.h"
#include <cstdlib>

const int MaxEquipo = 6;

/**
 * @class Equipo
 */
class Equipo {
private:
    Pokemon* datos;
    int tam;

public:

    Equipo();
    ~Equipo();

    /**
     * @param p
     * @return
     */
    bool agregar(const Pokemon& p);

    /**
     * @param id
     * @return
     */
    bool eliminar(int id);

    /**
     * @param id
     * @return
     */
    Pokemon* buscar(int id);

    bool estaVacio() const;
    bool estaLleno() const;

    /**
     * @return
     */
    int getTam() const;

    /**
     * @param indice
     * @return
     */
    const Pokemon& getDato(int indice) const;

    void mostrarTodos() const;
};

#endif