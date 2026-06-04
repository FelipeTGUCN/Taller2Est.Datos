#ifndef POKEMON_H
#define POKEMON_H

#include <string>
using namespace std;

/**
 * @class Movimiento
 */
struct Movimiento {
    string nombre;
    char   categoria;
    int    valor;
};

/**
 * @class Pokemon
 */
class Pokemon {
private:
    int id;
    string nombre;
    int cx;
    int bx;
    int dx;
    int ix;
    int ux;
    Movimiento movimientos[3];

public:
    Pokemon();

    /**
     * @param id
     * @param nombre
     * @param cx
     * @param bx
     * @param dx
     * @param ix
     * @param ux
     * @param mov1
     * @param mov2
     * @param mov3
     */
    Pokemon(int id, const string& nombre,
        int cx, int bx, int dx, int ix, int ux,
        const Movimiento& mov1,
        const Movimiento& mov2,
        const Movimiento& mov3);

    int getId() const;

    string getNombre() const;

    int getCx() const;

    int getBx() const;

    int getDx() const;

    int getIx() const;

    int getUx() const;

    /**
     * @param categoria
     * @return
     */
    int getStatPorCategoria(char categoria) const;

    /**
     * @param indice
     * @return
     */
    const Movimiento& getMovimiento(int indice) const;

    /**
     * @param id
     */
    void setId(int id);

    /**
     * @param nombre
     */
    void setNombre(const string& nombre);

    /**
     * @param cx
     */
    void setCx(int cx);

    /**
     * @param bx
     */
    void setBx(int bx);

    /**
     * @param dx
     */
    void setDx(int dx);

    /**
     * @param ix
     */
    void setIx(int ix);

    /**
     * @param ux
     */
    void setUx(int ux);

    /**
     * @param indice
     * @param mov
     */
    void setMovimiento(int indice, const Movimiento& mov);

    void mostrar() const;
};

#endif