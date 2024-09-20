/*
 * Declara los algortimos a usar en la resolución del
 * puzzle de sokorobotto. 
 * Los algorítmos se basan en búsqueda heúristica.
 * 
 * @author Fernando Broncano Morgado
 * @author Juan Francisco García Hinojosa
 * @author Antonio Javier Hidalgo Fernandez
 */

#ifndef _ALGORITMO_H
#define _ALGORITMO_H

#include "Tablero.h"
#include <vector>
#include <chrono>

using namespace std;

class Algoritmo {
private:

    // Marca temporal inicial de ejecucion del algoritmo
    chrono::_V2::system_clock::time_point tiempoInicial;

    // Marca temporal final de ejecucion del algoritmo
    chrono::_V2::system_clock::time_point tiempoFinal;

    // Tablero al que buscar solución
    Tablero* tablero;

    // Conjunto de las posiciones de cajas a colocar
    vector<Posicion> cajas;

    // Conjunto de las posiciones objetivos
    vector<Posicion> objetivos;

    // Conjunto de movivmientos realizados para llegar al estado final
    vector<string> movimientos;

    // Conjunto de las cajas ya colocadas y que han sido movidas
    vector<Posicion> cajasDescolocadas;

    // Conjunto de las posiciones objetivo que estaban ocupadas y se han desocupado
    vector<Posicion> objetivosCambiados;
    
    // Conjunto de las cajas ya colocadas y que han sido movidas
    vector<Posicion> cajasColocadas;

    // Conjunto de las posiciones objetivo que estaban ocupadas y se han desocupado
    vector<Posicion> objetivosUsados;

    // Número de nodos generados por un algoritmo
    int numNodos;
    
    /*
     * Recorre la matriz del estado inicial para obtener
     * las posiciones de las cajas y de los objetivos.
     */
    void obtenerPosiciones();

    /*
     * Función heurística para la resolución del problema.
     * Se calcula como la suma de las distancias entre la caja y el
     * objetivo, el objetivo y el robot, y, la caja y el robot.
     * 
     * @param caja la posicion de la caja seleccionada
     * @param objetivo la posicion objetivo seleccionada
     * @param nuevo el estado base para calcular la función
     * @param intercambio indica si se ha producido un movimiento de intercambio
     * 
     * @return el valor de la funcion heuristica calculado
     */
    int heuristica(Posicion caja, Posicion objetivo, Tablero* nuevo, bool intercambio);

    /*
     * Lanza la ejecución el algortimo indicado por el constructor.
     *
     * @param algoritmo el indice del algortimo a usar
     */
    void lanzarAlgoritmo(int algoritmo);

    /*
     * Algortimo de escalada simple. Su función es ir mejorando
     * la heuristica, quedándonos con el primer estado que vaya 
     * mejorando este valor. Trata de conseguir la solución del
     * tablero.
     * 
     * @return true si hay solución, false en otro caso
     */
    bool escaladaSimple();

    /*
     * Algoritmo de escalada por máxima pendiente.
     */
    bool maximaPendiente();

    /*
     *
     */
    bool busquedaPrimero();

public: 

    /*
     * Inicia el tablero con el fichero indicado en la interfaz
     * Tablero. Usa el algoritmo pasado por parametro. Los valores
     * posibles son:
     * 1 - Escalada Simple
     * 2 - Máxima Pendiente
     * 
     * @param algoritmo el indice del algortimo a usar
     */
    Algoritmo(int algoritmo);

    /*
     * Inicia el tablero con el fichero pasado por parametro y lo intenta
     * resolver. Usa el algoritmo indicado para la resolución del problema. 
     * Los valores posibles:
     * 1 - Escalada Simple
     * 2 - Máxima Pendiente
     * 
     * @param algoritmo el indice del algooritmo a usar
     * @param fichero la ruta al fichero a cargar.
     */
    Algoritmo(int algoritmo, string fichero);

    /*
     * Elimina una instancia de la clase Algoritmo, eliminando la memoria 
     * usada por el tablero, y los tableros padres que contiene.
     */
    ~Algoritmo();
};

#endif