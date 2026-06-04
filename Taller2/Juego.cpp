#include "Juego.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>   
#include <chrono>
#include <algorithm> 
#include <iomanip>
#include <limits>
using namespace std;

Juego::Juego() : pc(nullptr), atributoFavorito('C') {}

Juego::~Juego() {
    delete pc;
    pc = nullptr;
}

string Juego::nombreCategoria(char cat) const {
    switch (cat) {
        case 'C': return "Carisma";
        case 'B': return "Belleza";
        case 'D': return "Dulzura";
        case 'I': return "Ingenio";
        case 'U': return "Dureza";
        default:  return "Desconocida";
    }
}

/**
 * Lee cada línea del archivo pokemon.txt con el formato:
 * ID;Nombre;CX;BX;DX;IX;UX;NomMov1;CategMov1;ValMov1;NomMov2;CategMov2;ValMov2;NomMov3;CategMov3;ValMov3
 */
bool Juego::cargarPokemon(string archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "[Error] No se pudo abrir: " << archivo << endl;
        return false;
    }

    string linea;
    while (getline(file, linea)) {
        if (linea.empty()) continue;

        string partes[16];
        int numPartes = 0;
        string temp = "";

        for (int i = 0; i < (int)linea.size(); i++) {
            if (linea[i] == ';' || linea[i] == ',') {
                partes[numPartes++] = temp;
                temp = "";
            }
            else {
                temp += linea[i];
            }
        }
        partes[numPartes++] = temp;

        if (numPartes < 16) continue;

        Movimiento mov1, mov2, mov3;
        mov1.nombre = partes[7];
        mov1.categoria = partes[8][0];
        mov1.valor = stoi(partes[9]);

        mov2.nombre = partes[10];
        mov2.categoria = partes[11][0];
        mov2.valor = stoi(partes[12]);

        mov3.nombre = partes[13];
        mov3.categoria = partes[14][0];
        mov3.valor = stoi(partes[15]);

        // Construir el Pokémon
        Pokemon p(stoi(partes[0]), partes[1],
            stoi(partes[2]), stoi(partes[3]),
            stoi(partes[4]), stoi(partes[5]),
            stoi(partes[6]),
            mov1, mov2, mov3);

        naturaleza.insertar(p);
    }

    file.close();
    return true;
}

/**
 * Lee cada línea del archivo entrenadores.txt con el formato:
 * Nombre;Descripcion;IDPoke1;IDPoke2;IDPoke3;IDPoke4
 */
bool Juego::cargarEntrenadores(string archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "[Error] No se pudo abrir: " << archivo << endl;
        return false;
    }

    string linea;
    int idx = 0;

    while (getline(file, linea) && idx < NumEntrenadores) {
        if (linea.empty()) continue;

        string partes[6];
        int numPartes = 0;
        string temp = "";

        for (int i = 0; i < (int)linea.size(); i++) {
            if (linea[i] == ';') {
                partes[numPartes++] = temp;
                temp = "";
            }
            else {
                temp += linea[i];
            }
        }
        partes[numPartes++] = temp; 

        if (numPartes < 6) continue; 

        entrenadores[idx].setNombre(partes[0]);
        entrenadores[idx].setDescripcion(partes[1]);

        for (int j = 2; j < 6; j++) {
            int idPoke = stoi(partes[j]);
            Pokemon* poke = naturaleza.buscar(idPoke);
            if (poke != nullptr) {
                entrenadores[idx].agregarPokemon(*poke);
                naturaleza.eliminar(idPoke);
            }
        }
        idx++;
    }

    file.close();
    return true;
}


void Juego::elegirAtributoFavorito() {
    cout << "========================================" << endl;
    cout << "   ELIGE TU ATRIBUTO FAVORITO" << endl;
    cout << "========================================" << endl;
    cout << "  1. Carisma (C)" << endl;
    cout << "  2. Belleza (B)" << endl;
    cout << "  3. Dulzura (D)" << endl;
    cout << "  4. Ingenio (I)" << endl;
    cout << "  5. Dureza  (U)" << endl;
    cout << "========================================" << endl;

    int opcion = 0;
    while (opcion < 1 || opcion > 5) {
        cout << "Seleccione una opcion (1-5): ";
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = 0;
        }
        if (opcion < 1 || opcion > 5) {
            cout << "  [!] Opcion invalida. Intente nuevamente." << endl;
        }
    }

    char opciones[] = {'C', 'B', 'D', 'I', 'U'};
    atributoFavorito = opciones[opcion - 1];
    cout << "  Atributo favorito elegido: "
         << nombreCategoria(atributoFavorito) << endl;
    cout << "========================================" << endl;
}

int Juego::mostrarMenuPrincipal() const {
    cout << endl;
    cout << "========================================" << endl;
    cout << "        POKEMON CONTEST - MENU"           << endl;
    cout << "========================================" << endl;
    cout << "  1. Explorar Naturaleza"                 << endl;
    cout << "  2. Gestionar PC"                        << endl;
    cout << "  3. Ver Equipo"                          << endl;
    cout << "  4. Liberar Pokemon"                     << endl;
    cout << "  5. Transferir desde PC"                 << endl;
    cout << "  6. Participar en Concurso"              << endl;
    cout << "  7. Salir"                               << endl;
    cout << "========================================" << endl;

    int opcion = 0;
    while (opcion < 1 || opcion > 7) {
        cout << "Seleccione una opcion: ";
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = 0;
        }
        if (opcion < 1 || opcion > 7) {
            cout << "Opcion invalida (1-7). Intente nuevamente." << endl;
        }
    }
    return opcion;
}

void Juego::explorarNaturaleza() {
    cout << endl << "=== EXPLORAR NATURALEZA ===" << endl;

    if (naturaleza.estaVacio()) {
        cout << "  No quedan Pokemon disponibles en la naturaleza." << endl;
        return;
    }

    int idAleatorio = (rand() % 80) + 1;

    Pokemon* encontrado = naturaleza.buscarSucesor(idAleatorio);

    if (encontrado == nullptr) {
        cout << "  No se encontro un Pokemon con ID >= " << idAleatorio
             << ". Captura fallida." << endl;
        return;
    }

    cout << "  Se encontro un Pokemon salvaje!" << endl;
    encontrado->mostrar();

    Pokemon capturado = *encontrado;
    naturaleza.eliminar(capturado.getId());

    if (!equipo.estaLleno()) {
        equipo.agregar(capturado);
        cout << "  " << capturado.getNombre()
             << " se unio a tu equipo!" << endl;
    } else {
        cout << "  Tu equipo esta lleno. "
             << capturado.getNombre()
             << " fue enviado al PC." << endl;
        pc->insertar(capturado);
    }
}

void Juego::gestionarPC() {
    int opcion = 0;
    while (opcion != 3) {
        cout << endl;
        cout << "========================================" << endl;
        cout << "              Gestionar PC"              << endl;
        cout << "========================================" << endl;
        cout << "  1. Ver todos los Pokemon del PC"       << endl;
        cout << "  2. Ver mejor Pokemon (Mayor atributo)" << endl;
        cout << "  3. Volver al menu principal"           << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = 0;
        }

        if (opcion == 1) {
            cout << endl << "=== POKEMON EN EL PC ===" << endl;
            if (pc->estaVacio()) {
                cout << "  El PC esta vacio." << endl;
            } else {
                cout << "  Atributo de ordenamiento: "
                     << nombreCategoria(atributoFavorito) << endl;
                for (int i = 0; i < pc->getTam(); i++) {
                    cout << "----------------------------------------" << endl;
                    pc->getDato(i).mostrar();
                }
                cout << "----------------------------------------" << endl;
            }

        } else if (opcion == 2) {
            cout << endl << "=== MEJOR POKEMON EN EL PC ===" << endl;
            if (pc->estaVacio()) {
                cout << "  El PC esta vacio." << endl;
            } else {
                cout << "  Mejor segun " << nombreCategoria(atributoFavorito)
                     << ":" << endl;
                pc->verMax().mostrar();
            }

        } else if (opcion != 3) {
            cout << "  [!] Opcion invalida. Intente nuevamente." << endl;
        }
    }
}

void Juego::verEquipo() const {
    cout << endl << "=== TU EQUIPO ACTIVO ===" << endl;
    if (equipo.estaVacio()) {
        cout << "  Tu equipo esta vacio." << endl;
        return;
    }
    equipo.mostrarTodos();
    cout << "  Total: " << equipo.getTam() << "/" << MaxEquipo << endl;
}

void Juego::liberarPokemon() {
    cout << endl << "=== LIBERAR POKEMON ===" << endl;

    if (equipo.estaVacio()) {
        cout << "  Tu equipo esta vacio. No hay Pokemon que liberar." << endl;
        return;
    }

    equipo.mostrarTodos();

    int id = 0;
    bool valido = false;
    while (!valido) {
        cout << "Ingrese el ID del Pokemon a liberar: ";
        if (!(cin >> id)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  Entrada invalida. Ingrese un numero entero." << endl;
            continue;
        }
        if (equipo.buscar(id) != nullptr) {
            valido = true;
        } else {
            cout << " No hay un Pokemon con ID " << id
                 << " en tu equipo. Intente nuevamente." << endl;
        }
    }

    Pokemon* pokemon = equipo.buscar(id);
    string nombrePoke = pokemon->getNombre();
    Pokemon copia = *pokemon;

    equipo.eliminar(id);
    naturaleza.insertar(copia);

    cout << "  !" << nombrePoke
         << " ha sido liberado y ha vuelto a la naturaleza!" << endl;
}

void Juego::transferirDesdePC() {
    cout << endl << "=== TRANSFERIR DESDE PC ===" << endl;

    if (pc->estaVacio()) {
        cout << "  El PC esta vacio. No hay Pokemon para transferir." << endl;
        return;
    }

    Pokemon transferido = pc->extraerMax();
    cout << "  Pokemon transferido desde el PC:" << endl;
    transferido.mostrar();

    if (!equipo.estaLleno()) {
        equipo.agregar(transferido);
        cout << "  " << transferido.getNombre()
             << " se unio a tu equipo!" << endl;
    } else {
        cout << "  Tu equipo esta lleno. Debes liberar un Pokemon." << endl;
        equipo.mostrarTodos();

        int id = 0;
        bool valido = false;
        while (!valido) {
            cout << "Ingrese el ID del Pokemon a liberar: ";
            if (!(cin >> id)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Entrada invalida. Ingrese un numero entero." << endl;
                continue;
            }
            if (equipo.buscar(id) != nullptr) {
                valido = true;
            } else {
                cout << "ID " << id
                     << "no pertenece a tu equipo. Intente nuevamente." << endl;
            }
        }

        Pokemon* pokeLiberar = equipo.buscar(id);
        string nombreLiberar = pokeLiberar->getNombre();
        Pokemon copiaLiberar = *pokeLiberar;

        equipo.eliminar(id);
        naturaleza.insertar(copiaLiberar);

        cout << nombreLiberar
             << " ha sido liberado y ha vuelto a la naturaleza!" << endl;

        equipo.agregar(transferido);
        cout << "  " << transferido.getNombre()
             << " se unio a tu equipo!" << endl;
    }
}

double Juego::factorModificador(char categoriaMov, char categoriaConcurso) const {
    if (categoriaMov == 'D') return 1.0;

    if (categoriaMov == categoriaConcurso) return 1.5;

    if ((categoriaMov == 'B' && categoriaConcurso == 'U') ||
        (categoriaMov == 'U' && categoriaConcurso == 'B')) return 0.5;

    if ((categoriaMov == 'C' && categoriaConcurso == 'I') ||
        (categoriaMov == 'I' && categoriaConcurso == 'C')) return 0.5;

    return 1.0;
}

double Juego::calcularPuntos(const Pokemon& pokemon, int movAsignado,
                              char categoriaConcurso, string& reaccion) const {
    int statBase   = pokemon.getStatPorCategoria(categoriaConcurso);
    const Movimiento& mov = pokemon.getMovimiento(movAsignado);
    double factor  = factorModificador(mov.categoria, categoriaConcurso);
    double valorMod = mov.valor * factor;

    if (factor > 1.0) {
        reaccion = "Le encanto al publico!";
    } else if (factor < 1.0) {
        reaccion = "Silencio incomodo...";
    } else {
        reaccion = "El publico aplaudio.";
    }

    return statBase + valorMod;
}

void Juego::participarEnConcurso() {
    cout << endl << "=== PARTICIPAR EN CONCURSO ===" << endl;

    if (equipo.getTam() < 4) {
        cout << "  Necesitas al menos 4 Pokemon en tu equipo para participar." << endl;
        return;
    }

    char categorias[] = {'C', 'B', 'D', 'I', 'U'};
    char categoriaConcurso  = categorias[rand() % 5];

    int indicesRivales[3];
    int elegidos = 0;
    bool usados[NumEntrenadores] = {false};

    while (elegidos < 3) {
        int idx = rand() % NumEntrenadores;
        if (!usados[idx]) {
            usados[idx] = true;
            indicesRivales[elegidos++] = idx;
        }
    }

    cout << "========================================" << endl;
    cout << "           GRAN CONCURSO"                << endl;
    cout << "           Region Aurantia"              << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "  !Bienvenidos al Gran Concurso de "
         << nombreCategoria(categoriaConcurso) << "!" << endl;
    cout << endl;
    cout << "  Hoy los entrenadores demostran su talento en:" << endl;
    cout << "  Categoria: " << nombreCategoria(categoriaConcurso) << endl;
    cout << endl;
    cout << "  ----------------------------------------" << endl;
    cout << "  Participantes:" << endl;
    cout << "  ----------------------------------------" << endl;
    cout << "  * Tu (Jugador)" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "  * " << entrenadores[indicesRivales[i]].getNombre() << endl;
    }
    cout << endl;
    cout << "========================================" << endl;
    cout << "  Preparate para el espectaculo..." << endl;
    cout << "  Presione ENTER para continuar" << endl;
    cout << "========================================" << endl;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    cout << endl;
    cout << "============================================" << endl;
    cout << "         PARTICIPAR EN CONCURSO"             << endl;
    cout << "============================================" << endl;
    cout << "  Debe seleccionar un Pokemon de su equipo:" << endl;

    for (int i = 0; i < equipo.getTam(); i++) {
        const Pokemon& p = equipo.getDato(i);
        cout << "--------------------------------------------" << endl;
        cout << "  Pokemon:[" << p.getNombre() << "]" << endl;
        cout << "  ID      :[" << p.getId() << "]" << endl;
        cout << "  Stats   : CX[" << p.getCx() << "] BX[" << p.getBx()
             << "] DX[" << p.getDx() << "] IX[" << p.getIx()
             << "] UX[" << p.getUx() << "]" << endl;
        cout << "  Movimientos disponibles:" << endl;
        for (int j = 0; j < 3; j++) {
            const Movimiento& m = p.getMovimiento(j);
            cout << "    (" << m.nombre << ")(" << m.categoria
                 << ") | Valor:[" << m.valor << "]" << endl;
        }
    }
    cout << "============================================" << endl;

    int idSeleccionado = 0;
    bool valido = false;
    while (!valido) {
        cout << "  Seleccione su Pokemon (Ingresar ID): ";
        if (!(cin >> idSeleccionado)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada invalida." << endl;
            continue;
        }
        if (equipo.buscar(idSeleccionado) != nullptr) {
            valido = true;
        } else {
            cout << "ID " << idSeleccionado
                 << " no pertenece a tu equipo." << endl;
        }
    }

    Pokemon pokemonJugador = *equipo.buscar(idSeleccionado);

    int movJugador = rand() % 3;

    Pokemon  pokemonsRivales[3];
    int      movsRivales[3];

    for (int i = 0; i < 3; i++) {
        const Equipo& equipoRival = entrenadores[indicesRivales[i]].getEquipo();
        int idxPoke = rand() % equipoRival.getTam();
        pokemonsRivales[i] = equipoRival.getDato(idxPoke);
        movsRivales[i]     = rand() % 3;
    }

   cout << endl;
    cout << "  Se han seleccionado los Pokemon para el concurso:" << endl;
    cout << endl;


    cout << "  ----------------------------------------" << endl;
    cout << "  Jugador" << endl;
    cout << "  ----------------------------------------" << endl;
    cout << "  Pokemon : " << pokemonJugador.getNombre() << endl;
    cout << "  ID      : " << pokemonJugador.getId() << endl;
    cout << "  Stats   : CX[" << pokemonJugador.getCx()
         << "] BX[" << pokemonJugador.getBx()
         << "] DX[" << pokemonJugador.getDx()
         << "] IX[" << pokemonJugador.getIx()
         << "] UX[" << pokemonJugador.getUx() << "]" << endl;
    const Movimiento& mJ = pokemonJugador.getMovimiento(movJugador);
    cout << "  Movimiento asignado:" << endl;
    cout << "    + " << mJ.nombre << " (" << mJ.categoria
         << ") | Valor: " << mJ.valor << endl;


    for (int i = 0; i < 3; i++) {
        cout << endl;
        cout << "  ----------------------------------------" << endl;
        cout << "  Entrenador " << (i+1) << " - "
             << entrenadores[indicesRivales[i]].getNombre() << endl;
        cout << "  ----------------------------------------" << endl;
        cout << "  Pokemon : " << pokemonsRivales[i].getNombre() << endl;
        cout << "  ID      : " << pokemonsRivales[i].getId() << endl;
        cout << "  Stats   : CX[" << pokemonsRivales[i].getCx()
             << "] BX[" << pokemonsRivales[i].getBx()
             << "] DX[" << pokemonsRivales[i].getDx()
             << "] IX[" << pokemonsRivales[i].getIx()
             << "] UX[" << pokemonsRivales[i].getUx() << "]" << endl;
        const Movimiento& mR = pokemonsRivales[i].getMovimiento(movsRivales[i]);
        cout << "  Movimiento asignado:" << endl;
        cout << "    + " << mR.nombre << " (" << mR.categoria
             << ") | Valor: " << mR.valor << endl;
    }

    cout << endl;
    cout << "========================================" << endl;
    cout << "  Todos los movimientos han sido asignados." << endl;
    cout << "  El concurso esta por comenzar..." << endl;
    cout << "  Presione ENTER para iniciar" << endl;
    cout << "========================================" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    double puntosJugador  = 0;
    double puntosRivales[3] = {0, 0, 0};

    for (int fase = 1; fase <= 4; fase++) {
        cout << endl;
        cout << "========================================" << endl;
        cout << "            FASE " << fase << " DE 4    " << endl;
        cout << "========================================" << endl;
        cout << "  Categoria del concurso: "
             << nombreCategoria(categoriaConcurso) << endl;
        cout << endl;
        cout << "  Los participantes ejecutan sus movimientos..." << endl;
        cout << endl;
        cout << "  ----------------------------------------" << endl;
        cout << "  Resultados de la fase:" << endl;
        cout << "  ----------------------------------------" << endl;

        string reaccionJ;
        double ptsFase = calcularPuntos(pokemonJugador, movJugador,
                                        categoriaConcurso, reaccionJ);
        puntosJugador += ptsFase;

        cout << left << setw(14) << "  Jugador"
             << "| " << pokemonJugador.getNombre()
             << " usa " << mJ.nombre
             << " (" << mJ.categoria << ")" << endl;
        cout << "              | "
             << pokemonJugador.getStatPorCategoria(categoriaConcurso)
             << " + (" << mJ.valor << " x "
             << factorModificador(mJ.categoria, categoriaConcurso)
             << ") = " << ptsFase << " | " << reaccionJ << endl;

        for (int i = 0; i < 3; i++) {
            string reaccionR;
            double ptsFaseR = calcularPuntos(pokemonsRivales[i], movsRivales[i],
                                             categoriaConcurso, reaccionR);
            puntosRivales[i] += ptsFaseR;

            const Movimiento& mRi = pokemonsRivales[i].getMovimiento(movsRivales[i]);
            cout << endl;
            cout << left << setw(14)
                 << ("  Entrenador " + to_string(i+1))
                 << "| " << pokemonsRivales[i].getNombre()
                 << " usa " << mRi.nombre
                 << " (" << mRi.categoria << ")" << endl;
            cout << "              | "
                 << pokemonsRivales[i].getStatPorCategoria(categoriaConcurso)
                 << " + (" << mRi.valor << " x "
                 << factorModificador(mRi.categoria, categoriaConcurso)
                 << ") = " << ptsFaseR << " | " << reaccionR << endl;
        }

        cout << endl;
        cout << "  ----------------------------------------" << endl;
        cout << "  Marcador acumulado:" << endl;
        cout << "  ----------------------------------------" << endl;
        cout << "  Jugador      : " << puntosJugador << endl;
        for (int i = 0; i < 3; i++) {
            cout << "  Entrenador " << (i+1) << " : " << puntosRivales[i] << endl;
        }

        cout << endl;
        cout << "========================================" << endl;
        cout << "  La fase ha terminado..." << endl;
        cout << "  Presione ENTER para continuar" << endl;
        cout << "========================================" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    struct Resultado {
        string nombre;
        double puntos;
    };

    Resultado resultados[4];
    resultados[0] = {"Jugador",                           puntosJugador};
    resultados[1] = {entrenadores[indicesRivales[0]].getNombre(), puntosRivales[0]};
    resultados[2] = {entrenadores[indicesRivales[1]].getNombre(), puntosRivales[1]};
    resultados[3] = {entrenadores[indicesRivales[2]].getNombre(), puntosRivales[2]};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {
            if (resultados[j].puntos < resultados[j+1].puntos) {
                Resultado tmp    = resultados[j];
                resultados[j]    = resultados[j+1];
                resultados[j+1]  = tmp;
            }
        }
    }

    cout << endl;
    cout << "========================================" << endl;
    cout << "       RESULTADO DEL CONCURSO"           << endl;
    cout << "========================================" << endl;

    double maxPuntos = resultados[0].puntos;
    int cantGanadores = 0;
    for (int i = 0; i < 4; i++) {
        if (resultados[i].puntos == maxPuntos) cantGanadores++;
    }

    if (cantGanadores > 1) {
        cout << "  !EMPATE! Los ganadores son:" << endl;
        for (int i = 0; i < 4; i++) {
            if (resultados[i].puntos == maxPuntos) {
                cout << "    * " << resultados[i].nombre << endl;
            }
        }
    } else {
        cout << "  !El ganador es: " << resultados[0].nombre << "!" << endl;
        if (resultados[0].nombre == "Jugador") {
            cout << "  !Felicitaciones, ganaste el concurso!" << endl;
        }
    }

    cout << endl;
    cout << "  Marcador final:" << endl;
    cout << "  ----------------------------------------" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "  " << left << setw(20) << resultados[i].nombre
             << ": " << resultados[i].puntos << endl;
    }
    cout << "========================================" << endl;
}

void Juego::iniciar() {
    srand(static_cast<unsigned int>(
        chrono::steady_clock::now().time_since_epoch().count()
        ));

    cout << "========================================" << endl;
    cout << "     BIENVENIDO A POKEMON CONTEST"       << endl;
    cout << "     Region de Aurantia"                 << endl;
    cout << "========================================" << endl;

    cout << "  Cargando datos..." << endl;
    if (!cargarPokemon("pokemon.txt")) {
        cerr << "  Error al cargar Pokemon. Verifique el archivo." << endl;
        return;
    }
    if (!cargarEntrenadores("entrenadores.txt")) {
        cerr << "  Error al cargar Entrenadores. Verifique el archivo." << endl;
        return;
    }
    cout << "  Datos cargados correctamente." << endl;
    cout << "  Pokemon disponibles en la naturaleza: "
         << naturaleza.cantidad() << endl;

    elegirAtributoFavorito();

    pc = new MaxHeap(atributoFavorito);

    int opcion = 0;
    while (opcion != 7) {
        opcion = mostrarMenuPrincipal();
        switch (opcion) {
            case 1: explorarNaturaleza();  break;
            case 2: gestionarPC();         break;
            case 3: verEquipo();           break;
            case 4: liberarPokemon();      break;
            case 5: transferirDesdePC();   break;
            case 6: participarEnConcurso(); break;
            case 7: break; 
            default: break;
        }
    }

    cout << endl;
    cout << "========================================" << endl;
    cout << "  Gracias por jugar Pokemon Contest"     << endl;
    cout << "  !Hasta pronto, entrenador!"            << endl;
    cout << "========================================" << endl;
}
