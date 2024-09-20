#include "Algoritmo.h"

int aes::heuristica(Posicion caja, Posicion objetivo, Tablero* nuevo, bool intercambio) {

    int heuristica = abs(caja.fil - objetivo.fil) + abs(caja.col - objetivo.col) 
                   + abs(caja.fil - nuevo -> getRobot().fil) + abs(caja.col - nuevo -> getRobot().col);

    heuristica = heuristica - 20 * nuevo -> numCajasColocadas();                   

    heuristica = (intercambio)? heuristica - 1 : heuristica;

    return heuristica;
}

int aes::funcionPonderada(int heuristica, Tablero* estado) {
    return 3*heuristica + 2*estado -> profundidad();
}

bool Algoritmo::aEstrella() {
    priority_queue<Nodo, vector<Nodo>, greater<Nodo>> abiertos;
    list<Nodo> estados;
    vector<Posicion>* cajas = nullptr, *objetivos = nullptr;
    Tablero* estado = nullptr;
    Nodo cima, nuevo;
    bool acabado = false, intercambio, posible, solucion;
    int heu;

    // Guardamos el estado inicial, con su heurística, en la cola de abiertos
    heu = aes::heuristica(tablero -> getCajas() -> at(0), tablero -> getObjetivos() -> at(0), tablero, false);
    abiertos.push({aes::funcionPonderada(heu, tablero), tablero});

    while(!acabado) {
        // Procesamos el nodo. Comprobamos si es solucion
        if(tablero -> esSolucion()) {
            acabado = true;
            solucion = true;
        } else {
            // Cogemos el primer nodo de la lista de abiertos y lo eliminamos
            cima = abiertos.top();
            abiertos.pop();
            tablero = cima.estado;
            cajas = tablero -> getCajas();
            objetivos = tablero -> getObjetivos();

            // Exploramos los estados que parten de la cima
            for(auto caja = cajas -> begin(); caja != cajas -> end(); caja++) {
                for(auto objetivo = objetivos -> begin(); objetivo != objetivos -> end(); objetivo++) {
                    for(auto opcion = 0; opcion < 5; opcion++) {
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
                            heu = aes::heuristica(*caja, *objetivo, estado, intercambio);
                            nuevo = {aes::funcionPonderada(heu, estado), estado};
                            
                            // Si es un nuevo estado, lo guardamos en la cola
                            bool encontrado = false;

                            // Buscamos el nodo en la lista de estados distintos generados
                            for(auto nodo = estados.begin(); nodo != estados.end() && !encontrado; nodo++) {
                                if(nuevo == *nodo){
                                    encontrado = true;
                                }
                            }

                            // Si no se ha enontrado, insertamos el nodo en la cola de estados abiertos
                            if(!encontrado) {
                                abiertos.push(nuevo);
                                estados.push_back(nuevo);
                            }
                        }
                    }
                }
            }

            // Via de escape para no saturar la CPU
            if(numNodos > 200000) {
            acabado = true; 
            solucion = false;
            }

            // No hay un estado solucion válido
            if(abiertos.size() == 0) {
            acabado = true; 
            solucion = false;
            }
        }   
    }

    // Copiamos el tablero final para poderlo mostrar
    tablero = new Tablero(tablero, true);

    // Mostramos la solucion
    mostrarSolucion(tablero);
    cout << endl;
    
    // Desencolamos los nodos que quedan abiertos
    while(!abiertos.empty()) {
        abiertos.pop();
    }

    // Borramos los estados generados. En estado están los estados abiertos y cerrados
    while(!estados.empty()) {
        cima = estados.back();
        delete cima.estado;
        estados.pop_back();
    }

    // Vaciamos el vector
    estados.clear();

    return solucion;
}