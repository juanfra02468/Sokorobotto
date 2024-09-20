/*
 * Representa la entidad fundamental del problema a resolver.
 * Contiene toda la información relevante para representar un tablero
 * del juego sokorobotto (sokoban).
 * 
 * @author Fernando Broncano Morgado
 * @author Juan Francisco Garcia Hinojosa
 * @author Antonio Javier Hidalgo Fernandez
 */
#ifndef TABLERO_H_
#define TABLERO_H_

#define N 10
#define FICHERO "entrada//SOKOBOTTO7.txt"
#define MAX_INT 3

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

/* 
 * Definición de la posicion. Contiene dos enteros: fila y columna.
 */
struct Posicion {

    // Fila de la posicion
    int fil;

    // Columna de la posicion
    int col;

    /*
     * Sobrecarga del operador de igualdad para permitir la comparación de
     * posiciones.
     * 
     * @param other la posicion con la que comparar
     * @return true si dos posiciones son iguales, false en otro caso
     */
    bool operator == (const Posicion& other);
};

class Tablero {
private:

    // La matriz que contiene la información del tablero
    int matriz[N][N];
    
    // La posicion del robot en la matriz
    Posicion robot;
    
    // Referencia al nodo que generó este tablero
    Tablero *padre;

    // Vector con las posiciones de las cajas en el tablero
    vector<Posicion> cajas;
    
    // Vector de posiciones objetivos en el tablero
    vector<Posicion> objetivos;
    
    // Número de intercambios disponibles en un estado
    int interDisp;
    
    // Movimiento realizado para llegar al tablero actual
    string mov;

    /*
     * Carga un fichero bien formado en los atributos de nuestro tablero.
     *
     * @param fichero el fichero del que cargar la información
     */
    void cargarFichero(string fichero);

    /*
     * Realiza un movimiento genérico del robot a la nueva posicion.
     * Guarda el movimiento realizado.
     * 
     * @param nueva la posicion a la que mover el robot
     * @param adyacente la posicion contigua en la dirección en la que se mueve el robot
     * @param mov el movimiento que se hace en este movimiento
     * @return true si se ha realizado el movimiento, false en otro caso
     */
    bool mover(Posicion nueva, Posicion adyacente, string mov);

public:

    /*
     * Inicia un tablero con los valores indicados en el fichero
     * definido en la cabecera de la libreria. El fichero debe estar
     * bien formado
     */
    Tablero();

    /*
     * Inicia un tablero con los valores indicados en el fichero pasado
     * por parámetro. El fichero debe estar bien formado.
     * 
     * @param fichero la ruta al fichero que cargar
     */
    Tablero(string fichero);

    /*
     * Inicia un tablero realizando una copia del tablero pasado por paramétro 
     * y guardando una referencia a este Tablero.
     * 
     * @param other el tablero que se desea copiar
     */
    Tablero(Tablero *other);

    /*
     * Inicia un tablero con una copia exacta del tablero pasado 
     * por paramétro.
     * 
     * @param other el tablero que se desea copiar
     * @param copia indica si es una copia exacta (true) o no (false)
     */
    Tablero(Tablero* other, bool copia);

    /*
     * Realiza el movimiento hacia arriba del robot.
     * 
     * @return true si se ha realizado el movimiento, false en otro caso
     */
    bool moverArriba();

    /*
     * Realiza el movimiento hacia la derecha del robot.
     * 
     * @return true si se ha realizado el movimiento, false en otro caso
     */
    bool moverDerecha();

    /*
     * Realiza el movimiento hacia abajo del robot.
     * 
     * @return true si se ha realizado el movimiento, false en otro caso
     */
    bool moverAbajo();

    /*
     * Realiza el movimiento hacia la izquierda del robot.
     * 
     * @return true si se ha realizado el movimiento, false en otro caso
     */
    bool moverIzquierda();

    /*
     * Realiza el movimiento de intercambio entre el robot y
     * una caja contigua.
     * 
     * @return true si se ha realizado el movimiento, false en otro caso
     */
    bool intercambiar();

    /*
     * Devuelve la referencia al nodo padre a partir del cual se ha generado
     * este tablero. Devuelve nullptr si no tiene padre.
     * 
     * @return la referencia al nodo a partir del que se ha creado
     */
    Tablero* getPadre();

    /*
     * Devuelve la posicion del robot en el tablero.
     *
     * @return la posicion del robot en la matriz
     */
    Posicion getRobot();

    /*
     * Devuelve la refencia al vector de cajas que contiene el tablero.
     *
     * @return la referencia al vector de cajas
     */
    vector<Posicion>* getCajas();

    /*
     * Devuelve la refencia al vector de objetivos que contiene el tablero.
     *
     * @return la referencia al vector de objetivos
     */
    vector<Posicion>* getObjetivos();

    /*
     * Devuelve el elemento que hay en una posicion de la matriz.
     *
     * @return el elemento de una posicion en la matriz
     */
    int getElemento(Posicion posicion);

    /*
     * Devuelve el movimiento a través del cual se ha llegado a este tablero.
     *
     * @return el movimiento a través del cual se ha llegado al tablero
     */
    string getMovimiento();

    /*
     * Muestra un tablero representando los elementos como:
     *
     * 0 -> Espacio en blanco -> " "
     * 1 -> Muro -> +
     * 2 -> Caja -> #
     * 3 -> Objetivo -> O
     * 4 -> Robot -> R
     */
    void mostrarTablero();

    /*
     * Comprueba si en todas las posiciones objetivos hay una caja.
     *
     * @return true si en todas las posciones objetivos hay situada una caja,
     *         false en otro caso
     */
    bool esSolucion();

    /*
     * Sobrecarga del operador de igualdad entre dos tableros.
     *
     * @param other el tablero con el que comparar
     * @return true si dos tableros son iguales, false en otro caso
     */
    bool operator == (const Tablero& other);

    /*
     * Devuelve el número de cajas que hay en las posiciones objetivos.
     *
     * @return el numero de cajas colocadas en los objetivos
     */
    int numCajasColocadas();

    /*
     * Devuelve la cantidad de nodos que tiene un determinado nodo hasta 
     * llegar al nodo raíz.
     * 
     * @return la profundidad del nodo
     */
    int profundidad();
};

#endif /* TABLERO_H_ */