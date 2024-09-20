/*
 * Definicion de la clase Algoritmo para lanzar la ejecución
 * de los modelos algoritmicos para resolver el proyecto 
 * sokorobotto.
 * 
 * @author Fernando Broncano Morgado
 * @author Juan Francisco García Hinojosa
 * @author Antonio Javier Hidalgo Fernández
 */

#ifndef ALGORITMO_H_
#define ALGORITMO_H_

#include "Tablero.h"
#include <chrono>
#include <queue>
#include <list>

/*
 * Estructura nodo para los algoritmos que requieren
 * guardar los estados en una cola. Formado por el 
 * peso de ese estado y el propio estado.
 */
struct Nodo {
    // Coste del tablero que contiene
    int heuristica;

    // El tablero estado que contiene
    Tablero* estado;

    /*
     * Sobrecarga del operador de igualdad para dos nodos
     *
     * @param other el otro nodo con el que comparar
     * @return true si los dos nodos tienen el mismo estado, false en otro caso
     */
    bool operator == (const Nodo& other);
};

/*
 * Implementación del comparador de nodos para poder usar
 * la cola con prioridad del std c++.
 * 
 * @param other el primer nodo a comparar
 * @param other1 el segundo nodo a comparar
 * @return true si heuristica de other mayor que heuristica de other1, false en otro caso.
 */
bool operator > (const Nodo& other, const Nodo& other1);

class Algoritmo {
private:
    
    // Marca temporal inicial de ejecucion del algoritmo
    chrono::_V2::system_clock::time_point tiempoInicial;

    // Marca temporal final de ejecucion del algoritmo
    chrono::_V2::system_clock::time_point tiempoFinal;

    // Tablero que usa en un instante el algoritmo
    Tablero* tablero;

    // Numero de nodos generados por el algoritmo
    int numNodos;

    /*
     * Lanza el algoritmo de escalada simple para el tablero
     * cargado en el algoritmo.
     * 
     * @return true si encuentra solucion, false si no la encuentra
     */
    bool escaladaSimple();

    /*
     * Lanza el algoritmo de máxima pendiente para el tablero
     * cargado en el algoritmo.
     * 
     * @return true si encuentra solucion, false si no la encuentra
     */
    bool maximaPendiente();

    /*
     * Lanza el algoritmo de búsqueda del primero mejor para el tablero
     * cargado en el algoritmo.
     * 
     * @return true si encuentra solucion, false si no la encuentra
     */
    bool busquedaPrimero();

    /*
     * Lanza el algoritmo de A* para el tablero
     * cargado en el algoritmo.
     * 
     * @return true si encuentra solucion, false si no la encuentra
     */
    bool aEstrella();

    /*
     * Lanza la ejecución del algoritmo indicado por paramétro. Los valores son:
     * + 1 - Escalada Simple
     * + 2 - Máxima Pendiente
     * + 3 - Búsqueda del primero mejor
     * + 4 - A*
     */
    void lanzarAlgoritmo(int algoritmo);

    /*
     * Muestra los movimientos realizados para llegar al estado
     * 
     * @param estado el estado del que se busca la solución
     */
    void mostrarSolucion(Tablero* estado);

public:

    /*
     * Lanza una instancia de la clase Algoritmo. Carga el fichero
     * establecido en Tablero.h y ejecuta el programa con el 
     * algortimo indicado. Los valores son:
     * 
     * + 1 - Escalada Simple
     * + 2 - Máxima Pendiente
     * + 3 - Búsqueda del primero mejor
     * + 4 - A*
     * 
     * @param algortimo el indice del algoritmo a ejecutar
     */
    Algoritmo(int algoritmo);

    /*
     * Lanza una instancia de la clase Algoritmo. Carga el fichero
     * indicado por parametro, que debe estar bien formado, y lanza
     * el programa con el algortimo indicado. Los valores son:
     * 
     * + 1 - Escalada Simple
     * + 2 - Máxima Pendiente
     * + 3 - Búsqueda del primero mejor
     * + 4 - A*
     * 
     * @param algortimo el indice del algoritmo a ejecutar
     * @param fichero la ruta al fichero bien formado a cargar
     */
    Algoritmo(int algoritmo, string fichero);
};

/*
 * Funciones heuristicas y de coste para cada uno de los algoritmos.
 * Variamos los parametros la función heuristica en cada algoritmo para
 * obtener mejores resultados
 *
 * sim - Escalada Simple
 * max - Máxima Pendiente
 * bus - Búsqueda Primero Mejor
 * aes - A Estrella
 * 
 * Implementadas en cada uno de los ficheros.
 * Todas ellas se calculan con la distancia de Manhattan entre el robot y la caja y 
 * la caja y el objetivo. Tienen en cuenta si se realiza un movimiento de intercambio
 * para cambiar al estado nuevo, así como el numero de cajas bien colocadas que hay.
 */
namespace sim{
    /*
     * Funcion heurística para el algortimo de Escalada Simple
     *
     * @param caja la posicion de la caja fijada para colocar
     * @param objetivo la posicion del objetivo donde queremos llevar la caja
     * @param nuevo el nuevo tablero donde está el movimiento
     * @param intercambio indica si se ha llegado a ese estado a traves de un intercambio
     * @return la heuristica calculada
     */
    int heuristica(Posicion caja, Posicion objetivo, Tablero* nuevo, bool intercambio);
}

namespace max{
    /*
     * Funcion heurística para el algortimo de Máxima Pendiente
     *
     * @param caja la posicion de la caja fijada para colocar
     * @param objetivo la posicion del objetivo donde queremos llevar la caja
     * @param nuevo el nuevo tablero donde está el movimiento
     * @param intercambio indica si se ha llegado a ese estado a traves de un intercambio
     * @return la heuristica calculada
     */
    int heuristica(Posicion caja, Posicion objetivo, Tablero* nuevo, bool intercambio);
}

namespace bus{
    /*
     * Funcion heurística para el algortimo de Búsqueda Primero Mejor
     *
     * @param caja la posicion de la caja fijada para colocar
     * @param objetivo la posicion del objetivo donde queremos llevar la caja
     * @param nuevo el nuevo tablero donde está el movimiento
     * @param intercambio indica si se ha llegado a ese estado a traves de un intercambio
     * @return la heuristica calculada
     */
    int heuristica(Posicion caja, Posicion objetivo, Tablero* nuevo, bool intercambio);
}

namespace aes{
    /*
     * Funcion heurística para el algortimo de A*
     *
     * @param caja la posicion de la caja fijada para colocar
     * @param objetivo la posicion del objetivo donde queremos llevar la caja
     * @param nuevo el nuevo tablero donde está el movimiento
     * @param intercambio indica si se ha llegado a ese estado a traves de un intercambio
     * @return la heuristica calculada
     */
    int heuristica(Posicion caja, Posicion objetivo, Tablero* nuevo, bool intercambio);

    /*
     * Funcion que calcula el coste de un estado. Se calcula como la suma
     * de la heuristica mas los movimientos necesarios para alcanzar ese estado
     * 
     * @param heuristica el calculo de la funcion heuristica
     * @param estado el nuevo estado donde se representa el movimiento
     * @return la funcion de coste para A*
     */
    int funcionPonderada(int heuristica, Tablero* estado);
}

#endif /* ALGORITMO_H_ */