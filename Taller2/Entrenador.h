#ifndef ENTRENADOR_H
#define ENTRENADOR_H
#include "Equipo.h"
#include <string>
using namespace std;

/**
 * @class Entrenador
 */
class Entrenador {
private:
    string nombre;
    string descripcion;
    Equipo equipo;

public:

    Entrenador();

    /**
     * @return
     */
    string getNombre() const;

    /**
     * @return
     */
    string getDescripcion() const;

    /**
     * @return
     */
    Equipo& getEquipo();

    /**
     * @return
     */
    const Equipo& getEquipo() const;

    /**
     * @param nombre
     */
    void setNombre(const string& nombre);

    /**
     * @param descripcion
     */
    void setDescripcion(const string& descripcion);

    /**
     * @param p
     */
    void agregarPokemon(const Pokemon& p);
};

const int NumEntrenadores = 15;

#endif