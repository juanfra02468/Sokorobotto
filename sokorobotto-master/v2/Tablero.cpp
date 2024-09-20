/*
 * Implementación de la libreria Tablero.h
 * 
 * @author Fernando Broncano Morgado
 * @author Juan Francisco Garcia Hinojosa
 * @author Antonio Javier Hidalgo Fernandez
 */

#include "Tablero.h"

bool Posicion::operator == (const Posicion& other) {
    // Devuelve true si la fila y columa de las dos posiciones son iguales
    return this -> fil == other.fil && 
           this -> col == other.col;
}

void Tablero::cargarFichero(string fichero) {
    ifstream entrada;
    string linea;
    int elemento;

    // Abrimos el fichero
    entrada.open(fichero);

    if(entrada.is_open()) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                // Obtenemos cada uno de los datos
                getline(entrada, linea, ',');
                elemento = stoi(linea);

                // Clasificamos los datos
                matriz[i][j] = elemento;

                if(elemento == 2) {
                    cajas.push_back({i, j});
                } else if(elemento == 3) {
                    objetivos.push_back({i, j});
                } else if(elemento == 4) {
                    robot = {i, j};
                }
            }
        }

        // Cerramos el fichero
        entrada.close();
    } else {
        cout << "Fichero no abierto" << endl;
    }
}

bool Tablero::mover(Posicion nueva, Posicion adyacente, string mov) {
    bool movido;

    // Comprobamos si la posicion es un muro
    if(matriz[nueva.fil][nueva.col] == 1) {
        movido = false;
    } else if(matriz[nueva.fil][nueva.col] == 2) {
        if(matriz[adyacente.fil][adyacente.col] != 1 &&
           matriz[adyacente.fil][adyacente.col] != 2) {

            // Mover la caja a la posicion adyacente
            matriz[adyacente.fil][adyacente.col] = 2;
            for(auto caja = cajas.begin(); caja != cajas.end(); caja++) {
                if(*caja == nueva) {
                    *caja = adyacente;
                }
            }
    
            // Mover el robot a la nueva posicion
            matriz[robot.fil][robot.col] = 0;
            matriz[nueva.fil][nueva.col] = 4;
            robot = nueva;

            this -> mov = "E" + mov;
            movido = true;
        }
    } else {
        // Al permitir el movimiento, realizamos el movimiento
        matriz[robot.fil][robot.col] = 0;
        matriz[nueva.fil][nueva.col] = 4;
        robot = nueva;
        this -> mov = mov;
        movido = true;
    }

    return movido;
}

Tablero::Tablero() {
    // Iniciamos el número de intercambios disponibles
    this -> interDisp = MAX_INT;

    // La referencia al padre se inicia a nulo
    this -> padre = nullptr;

    // Iniciamos el movimiento a vacio
    this -> mov = "";

    // Añadimos los datos del fichero al tablero
    cargarFichero(FICHERO);
}

Tablero::Tablero(string fichero) {
    // Iniciamos el número de intercambios disponibles
    this -> interDisp = MAX_INT;

    // La referencia al padre se inicia a nulo
    this -> padre = nullptr;

    // Iniciamos el movimiento a vacio
    this -> mov = "";

    // Añadimos los datos del fichero al tablero
    cargarFichero(fichero);
}

Tablero::Tablero(Tablero *other) {
    // Copiamos la posicion del robot
    this -> robot = other -> robot;

    // Copiamos el numero de intercambios disponibles
    this -> interDisp = other -> interDisp;

    // Añadimos la referencia al padre
    this -> padre = other;

    // Iniciamos el movimiento a vacio
    this -> mov = "";

    // Copiamos el vector de las posiciones de cajas
    for(auto caja = other -> cajas.begin(); caja != other -> cajas.end(); caja++) {
        this -> cajas.push_back(*caja);
    }

    // Copiamos el vector de las posiciones objetivos
    for(auto obj = other -> objetivos.begin(); obj != other -> objetivos.end(); obj++) {
        this -> objetivos.push_back(*obj);
    }

    // Copiamos la matriz
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            this -> matriz[i][j] = other -> matriz[i][j];
        }
    }
}

Tablero::Tablero(Tablero* other, bool copia) {
    // Copiamos los datos con el otro constructor
    *this = Tablero(other);

    if(copia) {
        // Cambiamos la información necesaria para realizar la copia exacta
        this -> mov = other -> mov;
        this -> padre = other -> padre;
    }
}

bool Tablero::moverArriba() {
    return mover({robot.fil - 1, robot.col}, {robot.fil - 2, robot.col}, "A");
}

bool Tablero::moverDerecha() {
    return mover({robot.fil, robot.col + 1}, {robot.fil, robot.col + 2}, "D");
}

bool Tablero::moverAbajo() {
    return mover({robot.fil + 1, robot.col}, {robot.fil + 2, robot.col}, "B");
}

bool Tablero::moverIzquierda() {
    return mover({robot.fil, robot.col - 1}, {robot.fil, robot.col - 2}, "I");
}

bool Tablero::intercambiar() {
    bool movido = false;
    bool posible = false;
    Posicion caja;
    
    // Comprobamos que haya intercambios disponibles
    if(this -> interDisp > 0) {
        // Comprobamos si se puede intercambiar en alguna direccion
        if(matriz[robot.fil - 1][robot.col] == 2) {
            caja = {robot.fil - 1, robot.col};
            mov = "IA";
            posible = true;
        } else if(matriz[robot.fil + 1][robot.col] == 2) {
            caja = {robot.fil + 1, robot.col};
            mov = "IB";
            posible = true;
        } else if(matriz[robot.fil][robot.col - 1] == 2) {
            caja = {robot.fil, robot.col - 1};
            mov = "II";
            posible = true;
        } else if(matriz[robot.fil][robot.col + 1] == 2) {
            caja = {robot.fil, robot.col + 1};
            mov = "ID";
            posible = true;
        }

        // Si es posible, realizamos el intercambio
        if(posible) {
            matriz[robot.fil][robot.col] = 2;
            matriz[caja.fil][caja.col] = 4;

            // Representamos los cambios en el vector
            for(auto it = cajas.begin(); it != cajas.end(); it++) {
                if(caja == *it) {
                    *it = caja;
                }
            }

            robot = caja;
            movido = true;
            interDisp--;
        }
    }

    return movido;}

Tablero* Tablero::getPadre() {
    return this -> padre;
}

Posicion Tablero::getRobot() {
    return this -> robot;
}

vector<Posicion>* Tablero::getCajas() {
    return & this -> cajas;
}

vector<Posicion>* Tablero::getObjetivos() {
    return & this -> objetivos;
}

int Tablero::getElemento(Posicion posicion) {
    return matriz[posicion.fil][posicion.col];
}

string Tablero::getMovimiento() {
    return mov;
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

bool Tablero::esSolucion() {
    bool solucion = true;

    for(auto obj = objetivos.begin(); obj != objetivos.end(); obj++) {
        if(matriz[obj -> fil][obj -> col] != 2) {
            solucion = false;
        }
    }

    return solucion;
}

bool Tablero::operator == (const Tablero& other) {
    bool diferente = false;
    bool igual = false;

    // Comparamos que las posiciones y los intercambios disp sean iguales
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

int Tablero::numCajasColocadas() {
    int cajasColocadas = 0;

    for(auto obj = objetivos.begin(); obj != objetivos.end(); obj++) {
        if(matriz[obj -> fil][obj -> col] == 2) {
            cajasColocadas++;
        }
    }

    return cajasColocadas;
}

int Tablero::profundidad() {
    Tablero* estado = this;
    int profundidad = 0;
    
    while(estado -> padre != nullptr) {
        estado = estado -> padre;
        profundidad++;
    }

    return profundidad;
}