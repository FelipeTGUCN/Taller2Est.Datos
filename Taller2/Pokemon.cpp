#include "Pokemon.h"
#include <iostream>
#include <iomanip>
using namespace std;


Pokemon::Pokemon()
    : id(0), nombre(""), cx(0), bx(0), dx(0), ix(0), ux(0) {
    for (int i = 0; i < 3; i++) {
        movimientos[i] = {"", ' ', 0};
    }
}

Pokemon::Pokemon(int id, const string& nombre,
                 int cx, int bx, int dx, int ix, int ux,
                 const Movimiento& mov1,
                 const Movimiento& mov2,
                 const Movimiento& mov3)
    : id(id), nombre(nombre), cx(cx), bx(bx), dx(dx), ix(ix), ux(ux) {
    movimientos[0] = mov1;
    movimientos[1] = mov2;
    movimientos[2] = mov3;
}


int    Pokemon::getId()     const { return id; }
string Pokemon::getNombre() const { return nombre; }
int    Pokemon::getCx()     const { return cx; }
int    Pokemon::getBx()     const { return bx; }
int    Pokemon::getDx()     const { return dx; }
int    Pokemon::getIx()     const { return ix; }
int    Pokemon::getUx()     const { return ux; }

int Pokemon::getStatPorCategoria(char categoria) const {
    switch (categoria) {
        case 'C': return cx;
        case 'B': return bx;
        case 'D': return dx;
        case 'I': return ix;
        case 'U': return ux;
        default:  return 0;
    }
}

const Movimiento& Pokemon::getMovimiento(int indice) const {
    return movimientos[indice];
}

void Pokemon::setId(int id)                        { this->id     = id; }
void Pokemon::setNombre(const string& nombre)       { this->nombre  = nombre; }
void Pokemon::setCx(int cx)                        { this->cx     = cx; }
void Pokemon::setBx(int bx)                        { this->bx     = bx; }
void Pokemon::setDx(int dx)                        { this->dx     = dx; }
void Pokemon::setIx(int ix)                        { this->ix     = ix; }
void Pokemon::setUx(int ux)                        { this->ux     = ux; }

void Pokemon::setMovimiento(int indice, const Movimiento& mov) {
    if (indice >= 0 && indice < 3) {
        movimientos[indice] = mov;
    }
}


void Pokemon::mostrar() const {
    cout << "  Pokemon : " << nombre << endl;
    cout << "  ID      : " << id     << endl;
    cout << "  Stats   : CX[" << cx << "] BX[" << bx << "] DX["
         << dx << "] IX[" << ix << "] UX[" << ux << "]" << endl;
    cout << "  Movimientos disponibles:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "    (" << movimientos[i].nombre << ")"
             << "(" << movimientos[i].categoria << ")"
             << " | Valor:[" << movimientos[i].valor << "]" << endl;
    }
}
