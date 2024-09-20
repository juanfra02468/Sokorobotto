#include "Algoritmo.h"

int max::heuristica(Posicion caja, Posicion objetivo, Tablero* nuevo, bool intercambio) {

    int heuristica = abs(caja.fil - objetivo.fil) + abs(caja.col - objetivo.col) 
                   + abs(caja.fil - nuevo -> getRobot().fil) + abs(caja.col - nuevo -> getRobot().col);

    heuristica = heuristica - 5 * nuevo -> numCajasColocadas();                   

    return heuristica;
}

bool Algoritmo::maximaPendiente() {
    vector<Posicion>* cajas = nullptr, *objetivos = nullptr;
    Tablero* estado = nullptr, *padre = nullptr, *mejor = nullptr;
    bool acabado = false, intercambio, posible, solucion, movido;
    int heuActual, heuCal, heuMejor;

    // Iniciamos la heuristica al valor entre el robot. la primera caja y primer objetivo
    heuActual = max::heuristica(tablero -> getCajas() -> at(0), tablero -> getObjetivos() -> at(0), tablero, false);

    while(!acabado) {
        // Procesamos el nodo. Comprobamos si es solucion
        if(tablero -> esSolucion()) {
            acabado = true;
            solucion = true;
        } else {
            cajas = tablero -> getCajas();
            objetivos = tablero -> getObjetivos();
            heuMejor = heuActual;
            movido = false;

            // Exploramos los estados que parten de la cima
            for(auto caja = cajas -> begin(); caja != cajas -> end(); caja++) {
                for(auto objetivo = objetivos -> begin(); objetivo != objetivos -> end(); objetivo++) {
                    for(int opcion = 0; opcion < 5; opcion++) {
                        // Creamos el nuevo nodo
                        estado = new Tablero(tablero);
                        intercambio = false;
                        numNodos++;

                        // Realizamos el movimiento
                        if(opcion == 0) {
                            posible = estado -> moverArriba();
                        } else if(opcion == 1) {
                            posible = estado -> moverDerecha();
                        } else if(opcion == 2) {
                            posible = estado -> moverAbajo();
                        } else if(opcion == 3) {
                            posible = estado -> moverIzquierda();
                        } else if(opcion == 4) {
                            posible = estado -> intercambiar();
                            intercambio = true;
                        }    

                        // Si es posible realizar el movimiento, calculamos la heuristica y lo almacenamos en los nodos abiertos
                        if(posible) {
                            // Calculamos esa heuristica con la caja
                            // Si se cambia la posicion de la caja se modifica la posicion en vector
                            heuCal = max::heuristica(*caja, *objetivo, estado, intercambio);
                            
                            // Si la heuristica calculada es mejor que la actual, cambiamos el estado.
                            if(heuCal < heuMejor) {
                                mejor = estado;
                                heuMejor = heuCal;
                                movido = true;
                            } else {
                                // Si no desechamos el estado
                                delete estado;
                            }
                        
                        } else {
                            // Desechamos el estado
                            delete estado;
                        }
                    }
                }
            }

            // Realizamos el movimiento. Si no hay movimiento terminamos el programa
            if(movido) {
                heuActual = heuMejor;
                this -> tablero = mejor;
            } else {
                acabado = true;
                solucion = false;
            }
        }
    }

    // Copiamos el tablero final para poderlo mostrar
    estado = tablero;
    tablero = new Tablero(tablero, true);

    // Mostramos la solucion
    mostrarSolucion(tablero);
    cout << endl;

    // Borramos los estados de la memoria
    while(estado != nullptr) {
        padre = estado -> getPadre();
        delete estado;
        estado = padre;
    }

    return solucion;
}