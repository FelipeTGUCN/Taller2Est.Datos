#ifndef JUEGO_H
#define JUEGO_H

#include "ABB.h"
#include "MaxHeap.h"
#include "Equipo.h"
#include "Entrenador.h"
#include <string>
using namespace std;

/**
 * @class Juego
 */
class Juego {
private:
    ABB naturaleza;
    MaxHeap* pc;
    Equipo equipo;
    Entrenador entrenadores[NumEntrenadores];
    char atributoFavorito;

    /**
     * @param archivo
     * @return
     */
    bool cargarPokemon(string archivo);

    /**
     * @param archivo
     * @return
     */
    bool cargarEntrenadores(string archivo);

    void explorarNaturaleza();

    void gestionarPC();

    void verEquipo() const;

    void liberarPokemon();

    void transferirDesdePC();

    void participarEnConcurso();

    /**
     * @param pokemon
     * @param movAsignado
     * @param categoríaConcurso
     * @param reaccion
     * @return
     */
    double calcularPuntos(const Pokemon& pokemon, int movAsignado,
        char categoriaConcurso, string& reaccion) const;

    /**
     * @param catMov
     * @param catConcurso
     * @return
     */
    double factorModificador(char catMov, char catConcurso) const;

    /**
     * @param cat
     * @return
     */
    string nombreCategoria(char cat) const;

    /**
     * @return
     */
    int mostrarMenuPrincipal() const;

    void elegirAtributoFavorito();

public:
    Juego();

    ~Juego();

    /**
     * @param rutaPokemon
     * @param rutaEntrenadores
     */
    void iniciar();
};

#endif