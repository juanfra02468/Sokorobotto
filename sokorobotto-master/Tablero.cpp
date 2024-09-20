/*
 * Implementación de la clase Tablero
 *
 * @author Fernando Broncano Morgado
 * @author Juan Francisco García Hinojosa
 * @author Antonio Javier Hidalgo Fernández
 */

#include "Tablero.h"

// Declaración privada
void Tablero::cargarDatos(string fichero) {
    ifstream entrada;
    string casilla;
    int elemento;
    Posicion pos;

    entrada.open(fichero, ios::in);

    if(entrada.is_open()){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                getline(entrada, casilla, ',');
                elemento = stoi(casilla);
                matriz[i][j] = elemento;
                
                if(elemento == 4){
                    robot = {i, j};
                }
            }
        }
    } else {
        cout << "Fichero no abierto" << endl;
    }

    entrada.close();
}

void Tablero::moverRobot(Posicion nueva) {
    matriz[robot.fila][robot.columna] = 0;
    matriz[nueva.fila][nueva.columna] = 4;
    robot = nueva;
}

void Tablero::moverCaja(Posicion anterior, Posicion nueva) {
    matriz[anterior.fila][anterior.columna] = 0;
    matriz[nueva.fila][nueva.columna] = 2;
}

// Declaracion Publica
Tablero::Tablero() {
    this -> intercambiosRestantes = 3;
    this -> cargarDatos(NOMBREFICHERO);
    this -> padre = nullptr;
}

Tablero::Tablero(string fichero) {
    this -> intercambiosRestantes = 3;
    this -> cargarDatos(fichero);
    this -> padre = nullptr;
}

Tablero::Tablero(Tablero *other) {
    intercambiosRestantes = other -> intercambiosRestantes;
    robot = other -> robot;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            matriz[i][j] = other -> matriz[i][j];
        }
    }

    this -> padre = other;
}

void Tablero::mostrarTablero() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {

            if(matriz[i][j] == 0) {
                cout << "   ";
            } else if(matriz[i][j] == 1) {
                cout << " + ";
            } else if(matriz[i][j] == 2) {
                cout << " # ";
            } else if(matriz[i][j] == 3) {
                cout << " O ";
            } else if(matriz[i][j] == 4) {
                cout << " R ";
            }
        }

        cout << endl;
    }
}

bool Tablero::mover(Posicion posicion, Posicion adyacente, string mov, Posicion* &nueva) {
    bool movido;
    nueva = nullptr;

    if(matriz[posicion.fila][posicion.columna] == 1) {
        movido = false;
        mov = "";
    } else if(matriz[posicion.fila][posicion.columna] == 2) {
        // Comprobar mover caja
        if(matriz[adyacente.fila][adyacente.columna] != 1 &&
            matriz[adyacente.fila][adyacente.columna] != 2 ) {        
            moverCaja(posicion, adyacente);
            moverRobot(posicion);
            nueva = new Posicion;
            *nueva = adyacente;
            movimiento = "E" + mov;
            movido = true;
        }
    } else {
        moverRobot(posicion);
        movimiento = mov;
        movido = true;
    }

    return movido;
}

// Movimientos
bool Tablero::moverArriba(Posicion* &nueva, Posicion &anterior) {
    anterior = {robot.fila - 1, robot.columna};
    return mover({robot.fila - 1, robot.columna}, {robot.fila - 2, robot.columna}, "A", nueva);
}

bool Tablero::moverAbajo(Posicion* &nueva, Posicion &anterior) {
    anterior = {robot.fila + 1, robot.columna};
    return mover({robot.fila + 1, robot.columna}, {robot.fila + 2, robot.columna}, "B", nueva);
}

bool Tablero::moverIzquierda(Posicion* &nueva, Posicion &anterior) {
    anterior = {robot.fila, robot.columna - 1};
    return mover({robot.fila, robot.columna - 1}, {robot.fila, robot.columna - 2}, "I", nueva);
}

bool Tablero::moverDerecha(Posicion* &nueva, Posicion &anterior) {
    anterior = {robot.fila, robot.columna + 1};
    return mover({robot.fila, robot.columna + 1}, {robot.fila, robot.columna + 2}, "D", nueva);
}

bool Tablero::intercambiar(Posicion* &nueva, Posicion &anterior) {
    bool movido = false;
    bool posible = false;
    Posicion caja;
    nueva = nullptr;

    if(intercambiosRestantes > 0) {
        if(matriz[robot.fila - 1][robot.columna] == 2) {
            caja = {robot.fila - 1, robot.columna};
            movimiento = "IA";
            posible = true;
        } else if(matriz[robot.fila + 1][robot.columna] == 2) {
            caja = {robot.fila + 1, robot.columna};
            movimiento = "IB";
            posible = true;
        } else if(matriz[robot.fila][robot.columna - 1] == 2) {
            caja = {robot.fila, robot.columna - 1};
            movimiento = "II";
            posible = true;
        } else if(matriz[robot.fila][robot.columna + 1] == 2) {
            caja = {robot.fila, robot.columna + 1};
            movimiento = "ID";
            posible = true;
        }

        if(posible) {
            matriz[robot.fila][robot.columna] = 2;
            matriz[caja.fila][caja.columna] = 4;
            nueva = new Posicion;
            *nueva = robot;
            anterior = caja;
            robot = caja;
            movido = true;
            intercambiosRestantes--;
        }
    }

    return movido;
}

string Tablero::getMovimiento() {
    return movimiento;
}

Posicion Tablero::getRobot() {
    return robot;
}

int Tablero::getElemento(int fila, int columna) {
    return matriz[fila][columna];
}

Tablero* Tablero::getPadre() {
    return padre;
}

bool Posicion::operator == (const Posicion& other) {
    return this -> fila == other.fila && 
           this -> columna == other.columna;
}

bool Tablero::operator == (const Tablero& other) {
    bool diferente = false;
    bool igual = false;

    if(this -> robot == other.robot){
        for(int i = 0; i < N && !diferente; i++) {
            for(int j = 0; j < N && !diferente; j++) {
                if(this -> matriz[i][j] != other.matriz[i][j]) {
                    diferente = true;
                }
            }
        }

        if(!diferente) {
            igual = true;
        }        
    }

    return igual;
}
