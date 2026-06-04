#include "Entrenador.h"


Entrenador::Entrenador() : nombre(""), descripcion("") {}

string Entrenador::getNombre()      const { return nombre; }
string Entrenador::getDescripcion() const { return descripcion; }

Equipo& Entrenador::getEquipo() {
    return equipo;
}

const Equipo& Entrenador::getEquipo() const {
    return equipo;
}


void Entrenador::setNombre(const string& nombre) {
    this->nombre = nombre;
}

void Entrenador::setDescripcion(const string& descripcion) {
    this->descripcion = descripcion;
}


void Entrenador::agregarPokemon(const Pokemon& p) {
    equipo.agregar(p);
}
