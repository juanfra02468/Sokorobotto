/*
 * La clase tablero define los componentes del
 * tablero de resolución. Permite realizar movimientos
 * y obtener los elementos necesarios para comprobar
 * el estado de resolución.
 * 
 * @author Fernando Broncano Morgado
 * @author Juan Francisco García Hinojosa
 * @author Antonio Javier Hidalgo Fernandez
 */

#ifndef _TABLERO_H
#define _TABLERO_H

#define N 10
#define NOMBREFICHERO "entrada//SOKOBOTTO10.txt"

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

/*
 * Declaración del tipo Posicion.
 * Contiene la fila y columna de un elemento
 * en la matriz.
 */
struct Posicion {
    int fila;
    int columna;

    bool operator == (const Posicion& other);
};

class Tablero {
private:

    // Matriz que representa el tablero
    int matriz[N][N];

    // Numero de intercambios disponibles
    int intercambiosRestantes;

    // Movimiento realizado en el estado
    string movimiento;

    // Posicion actual del robot en la matriz
    Posicion robot;

    // Tablero padre
    Tablero* padre;

    /*
     * Carga los datos del fichero en un Tablero.
     * EL fichero debe estar bien formado
     * 
     * @param fichero ruta al fichero a cargar
     */
    void cargarDatos(string fichero);

    /*
     * Mueve la posicion del robot a la indicada.
     *
     * @param nueva la nueva posicion del robot.
     */
    void moverRobot(Posicion nueva);

    /*
     * Mueve la caja a la posicion indicada.
     *
     * @param anterior la posicion donde está la caja
     * @param nueva la posicion donde poner la caja
     */
    void moverCaja(Posicion anterior, Posicion nueva);
   
    /*
     * Mueve el robot a la posición indicando el tipo de movimiento
     *
     * @param posicion la posicion a la que mover
     * @param adyacente la posicion contigua a la que mover siguiendo el mismo mov
     * @param mov el movimiento a realizar
     */
    bool mover(Posicion posicion, Posicion adyacente, string mov, Posicion* &nueva);

public:

    /*
     * Crea un tablero iniciado con el fichero definido en la 
     * cabecera.
     */
    Tablero();

    /*
     * Crea un tablero copia de otro pasado por paramétro.
     *
     * @param other el tablero que copiar en el nuevo
     */
    Tablero(Tablero* other);

    /*
     * Crea un tablero iniciado con el fichero indicado.
     *
     * @param fichero la ruta al fichero que cargar
     */
    Tablero(string fichero);
    
    /*
     * Intenta mover el robot a la posición por encima. Si
     * hubiera una caja, la empuja si es posible.
     * 
     * @param nueva la nueva posicion de la caja
     * @param anterior la anterior posicion de la caja
     * @return true si se ha movido, false en otro caso
     */
    bool moverArriba(Posicion* &nueva, Posicion &anterior);

    /*
     * Intenta mover el robot a la posición por debajo. Si
     * hubiera una caja, la empuja si es posible.
     * 
     * @param nueva la nueva posicion de la caja
     * @param anterior la anterior posicion de la caja
     * @return true si se ha movido, false en otro caso
     */
    bool moverAbajo(Posicion* &nueva, Posicion &anterior);

    /*
     * Intenta mover el robot a la posición de su izquierda. Si
     * hubiera una caja, la empuja si es posible.
     * 
     * @param nueva la nueva posicion de la caja
     * @param anterior la anterior posicion de la caja
     * @return true si se ha movido, false en otro caso
     */
    bool moverIzquierda(Posicion* &nueva, Posicion &anterior);

    /*
     * Intenta mover el robot a la posición a su derecha. Si
     * hubiera una caja, la empuja si es posible.
     * 
     * @param nueva la nueva posicion de la caja
     * @param anterior la anterior posicion de la caja
     * @return true si se ha movido, false en otro caso
     */
    bool moverDerecha(Posicion* &nueva, Posicion &anterior);

    /*
     * Intenta intercambiar el robot con una caja si están contiguas.
     * Debe haber intercambios disponibles.
     * 
     * @param nueva la nueva posicion de la caja
     * @param anterior la anterior posicion de la caja
     * @return true si se ha intercambiado, false en otro caso
     */
    bool intercambiar(Posicion* &nueva, Posicion &anterior);

    /*
     * Muestra el tablero guardado. Los elementos mostrados son:
     * + '+' - Representa un muro
     * + 'R' - Representa la posicion del robot
     * + 'O' - Representa la posición objetivo
     * + '#' - Representa una caja
     * Los espacios en blanco representan casillas vacias
     */
    void mostrarTablero();

    /*
     * Devuelve el movimiento realizado en este estado del 
     * tablero.
     *
     * @return el movimiento realizado en este estado
     */
    string getMovimiento();

    /*
     * Devuelve la posición del robot en el tablero.
     *
     * @return la posicion del robot en el tablero
     */
    Posicion getRobot();

    /*
     * Devuelve el elemento que hay en una fila y columna
     * de la matriz.
     * 
     * @param fila la fila de la posicion a obtener el elemento
     * @param columna la columna de la posicion a obtener el elemento
     * @return el elemento en la fila y columna indicadas
     */
    int getElemento(int fila, int columna);

    /*
     * Devuelve el enlace al nodo padre.
     *
     * @return el puntero al nodo padre.
     */
    Tablero* getPadre();

    /*
     *
     */
    bool operator == (const Tablero& other);
};

#endif