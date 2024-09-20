/*
 * Implementación de los algortimos de búsqueda
 * heurística.
 * 
 * @author Fernando Broncano Morgado
 * @author Juan Francisco García Hinojosa
 * @author Antonio Javier Hidalgo Fernandez
 */

#include "Algoritmo.h"
    
Algoritmo::Algoritmo(int algoritmo) {
    this -> numNodos = 0;
    this -> tablero = new Tablero();
    this -> obtenerPosiciones();
    this -> lanzarAlgoritmo(algoritmo);
}
    
Algoritmo::Algoritmo(int algoritmo, string fichero) {
    this -> numNodos = 0;
    this -> tablero = new Tablero(fichero);
    this -> obtenerPosiciones();
    this -> lanzarAlgoritmo(algoritmo);
}

void Algoritmo::obtenerPosiciones() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int pos = tablero -> getElemento(i, j);
            if(pos == 2) {
                cajas.push_back({i, j});
            } else if(pos == 3) {
                objetivos.push_back({i, j});
            }
        }
    }
}

void Algoritmo::lanzarAlgoritmo(int algoritmo) {
    bool solucion;

    tablero -> mostrarTablero();

    // Lanzamos la ejecución del algortimo
    tiempoInicial = chrono::high_resolution_clock::now();

    if(algoritmo == 1) {
        solucion = escaladaSimple();
    } else if(algoritmo == 2) {
        solucion = maximaPendiente();
    } else if(algoritmo == 3) {
        solucion = busquedaPrimero();
    }

    tiempoFinal = chrono::high_resolution_clock::now();
        
    // Mostramos si tiene solución
    if(solucion) {
        cout << "Se ha encontrado solucion" << endl;
    } else {
        cout << "No se ha encontrado solucion" << endl;
    }

    for(string mov : movimientos) {
        cout << mov << ",";
    }

    // Mostramos los datos relevantes
    cout << endl << "Tiempo empleado: " 
         << chrono::duration_cast<chrono::nanoseconds>(tiempoFinal - tiempoInicial).count() 
         << "ns." << endl
         << "Numero de nodos generados: " << numNodos << endl << endl;

    // Mostramos el tablero
    tablero -> mostrarTablero();
}

int Algoritmo::heuristica(Posicion caja, Posicion objetivo, Tablero* nuevo, bool intercambio) {
    
    int heuristica = abs(caja.fila - objetivo.fila) + abs(caja.columna - objetivo.columna) 
                   + abs(caja.fila - nuevo -> getRobot().fila) + abs(caja.columna - nuevo -> getRobot().columna)
                   + abs(objetivo.fila - nuevo -> getRobot().fila) + abs(objetivo.columna - nuevo ->getRobot().columna);
    
    return (intercambio)? heuristica - 1 : heuristica;
}

bool Algoritmo::escaladaSimple() {
    bool acabado = false, posible, movido, intercambio;
    Tablero *estado = nullptr;
    Posicion *nueva = nullptr, anterior;
    int heuActual, heuNueva;

    // La primera heurística es la distancia entre la posicion del robot
    // la primera caja insertada y el primer objetivo insertado
    heuActual = heuristica(cajas[0], objetivos[0], this -> tablero, false);

    // Mientras que el programa no haya llegado a su fin
    while(!acabado) {
        movido = false;

        // Comprobamos las opciones disponibles hasta que mejore la heuristica
        for(auto caja = cajas.begin(); caja != cajas.end() && !movido; caja++) {
            for(auto objetivo = objetivos.begin(); objetivo != objetivos.end() && !movido; objetivo++) {
                for(auto opcion = 0; opcion < 5 && !movido; opcion++) {
                    
                    // Lanzamos un nuevo nodo
                    estado = new Tablero(this -> tablero);
                    intercambio = false;
                    numNodos++;

                    // Realizamos el movimiento
                    if(opcion == 0) {
                        posible = estado -> moverArriba(nueva, anterior);
                    } else if(opcion == 1) {
                        posible = estado -> moverDerecha(nueva, anterior);
                    } else if(opcion == 2) {
                        posible = estado -> moverAbajo(nueva, anterior);
                    } else if(opcion == 3) {
                        posible = estado -> moverIzquierda(nueva, anterior);
                    } else if(opcion == 4) {
                        posible = estado -> intercambiar(nueva, anterior);
                        intercambio = true;
                    }     

                    // Si es posible realizar el movimiento, comprobamos si es un estado mejor
                    if(posible) {
                        // Si la caja ha sido movida, calculamos esa heuristica con la caja
                        if(nueva != nullptr) {
                            // Comprobamos que la caja que se haya movido es la del estado
                            if(caja -> fila == anterior.fila && caja -> columna == anterior.columna) {
                                heuNueva = heuristica(*nueva, *objetivo, estado, intercambio);
                            } else {
                                // Si se ha movido otra caja, se calcula con la caja seleccionada
                                heuNueva = heuristica(*caja, *objetivo, estado, intercambio);
                            }
                        } else {
                            heuNueva = heuristica(*caja, *objetivo, estado, intercambio);
                        }

                        // Si la heurística mejora, nos quedamos con este estado
                        if(heuNueva < heuActual) {
                            tablero = estado;
                            heuActual = heuNueva;
                            movido = true;
                        } else {
                            // Si la heurística no mejora, desechamos los datos
                            delete estado;
                            delete nueva;
                        }
                    } else {
                        // Si no es posible el movimiento, borramos los datos
                        delete estado;
                        delete nueva;
                    }
                }
            }
        }

        // Si se hace el movimiento, cambiamos el estado de las cajas
        if(movido) {
            // Cambiamos las posiciones de las cajas en los vectores si se han movido
            if(nueva != nullptr) {
                bool encontrado = false;

                // Buscamos la caja en el vector de cajas
                for(auto it = cajas.begin(); it != cajas.end(); it++) {
                    if(it -> fila == anterior.fila &&
                       it -> columna == anterior.columna) {
                        // Si esa posicion se ha modificado, cambiamos la anterior posicion
                        *it = *nueva;
                        encontrado = true;
                    }
                }

                // Si no encontramos la caja en el vector de cajas esta ha sido 
                // colocada y ahora movida. Cambiamos su estado. La quitamos de 
                // las cajas colocadas y la pasamos a las cajas pendientes de colocar
                if(!encontrado) {
                    encontrado = false;
                    for(auto it = cajasDescolocadas.begin(); it != cajasDescolocadas.end(); it++) {
                        if(it -> fila == anterior.fila &&
                           it -> columna == anterior.columna) {
                            *it = *nueva;
                            encontrado = true;
                        }
                    }

                    // Si no está en cajasDecolocadas, lo borramos de cajasColocadas y lo insertamos
                    // Tambien cambiamos el objetivo usado por el objetivo cambiado
                    if(!encontrado) {
                        // Buscamos la caja colocada que se ha movido y la borramos
                        for(auto it = cajasColocadas.begin(); it != cajasColocadas.end(); it++) {
                            if(it -> fila == anterior.fila &&
                               it -> columna == anterior.columna) {
                                cajasColocadas.erase(it);
                                break;
                            }
                        }

                        // Buscamos el objetivo usado a la lista de cambiados
                        for(auto it = objetivosUsados.begin(); it != objetivosUsados.end(); it++) {
                            if(it -> fila == anterior.fila &&
                               it -> columna == anterior.columna) {
                                objetivosUsados.erase(it);
                                break;
                            }    
                        }

                        //Insertamos el objetivo borrado en los objetivos que han sido cambiados
                        objetivosCambiados.push_back(anterior);

                        // Insertamos la nueva posicion de la caja
                        cajasDescolocadas.push_back(*nueva);
                    }
                }
            }

            // Guardamos el movimiento realizado en el vector de movimientos
            if(tablero -> getMovimiento() != "") {
                movimientos.push_back(tablero -> getMovimiento());
            }

            // Borramos los datos del movimiento
            delete nueva;
            nueva = nullptr;
            movido = true;
        }

        // Comprobamos si alguna caja ha llegado a su objetivo
        // Si todas estan colocadas, hemos encontrado solución
        bool borrado = false;
        for(auto caja = cajas.begin(); caja != cajas.end() && !borrado; caja++) {
            for(auto objetivo = objetivos.begin(); objetivo != objetivos.end() && !borrado; objetivo++) {
                // Si la posicion de la caja y el objetivo son iguales
                // Esa caja se ha colocado. Borramos la caja y el objetivo de los disponibles
                if(caja -> fila == objetivo -> fila &&
                   caja -> columna == objetivo -> columna) {
                    objetivosUsados.push_back(*objetivo);
                    cajasColocadas.push_back(*caja);
                    cajas.erase(caja);
                    objetivos.erase(objetivo);

                    // Si se ha borrado una caja. Reseteamos la heurística
                    if(cajas.size() > 0 && objetivos.size() > 0) {
                        heuActual = heuristica(cajas[0], objetivos[0], this -> tablero, intercambio);
                    } else {
                        heuActual = INT_MAX;
                    }
                    borrado = true;
                }
            }
        }
    
        // Comprobamos que estan todas las cajas colocadas
        if(cajas.size() == 0) {
            // Si no hay cajas por colocar y tampoco hay cajas que se
            // hayan movido estando colocadas -> terminamos
            if(cajasDescolocadas.size() == 0) {
                acabado = true;
            } else {
                // Intentamos colocar las cajas que se han movido estando colocadas
                for(auto caja = cajasDescolocadas.begin(); caja != cajasDescolocadas.end(); caja++) {
                    cajas.push_back(*caja);
                }

                for(auto objetivo = objetivosCambiados.begin(); objetivo != objetivosCambiados.end(); objetivo++) {
                    objetivos.push_back(*objetivo);
                }

                objetivosCambiados.clear();
                cajasDescolocadas.clear();
                heuActual = heuristica(cajas[0], objetivos[0], tablero, intercambio);
            }
        }

        // Si no se ha hecho ningún movimiento, cortamos la ejecución
        if(!movido) {
            acabado = true;
        }

    }

    // Si en el último movimiento se ha movido, hemos encontrado solucion
    return movido;
}

bool Algoritmo::maximaPendiente() {
    bool acabado = false, posible, movido, intercambio;
    Tablero *estado = nullptr, *estadoMejor = nullptr;
    Posicion *nueva, anterior, *nuevaMejor = nullptr, anteriorMejor;
    int heuActual, heuNueva, heuMejor;

    // La primera heurística es la distancia entre la posicion del robot
    // la primera caja insertada y el primer objetivo insertado
    heuActual = heuristica(cajas[0], objetivos[0], this -> tablero, false);

    // Mientras que el programa no haya llegado a su fin
    while(!acabado) {
        movido = false;
        
        // La mejor heuristica hasta ahora es la actual
        heuMejor = heuActual;

        // Comprobamos todas las opciones disponibles
        for(auto caja = cajas.begin(); caja != cajas.end(); caja++) {
            for(auto objetivo = objetivos.begin(); objetivo != objetivos.end(); objetivo++) {
                for(auto opcion = 0; opcion < 5; opcion++) {
                    
                    // Lanzamos un nuevo nodo
                    estado = new Tablero(this -> tablero);
                    intercambio = false;
                    numNodos++;

                    // Realizamos el movimiento
                    if(opcion == 0) {
                        posible = estado -> moverArriba(nueva, anterior);
                    } else if(opcion == 1) {
                        posible = estado -> moverDerecha(nueva, anterior);
                    } else if(opcion == 2) {
                        posible = estado -> moverAbajo(nueva, anterior);
                    } else if(opcion == 3) {
                        posible = estado -> moverIzquierda(nueva, anterior);
                    } else if(opcion == 4) {
                        posible = estado -> intercambiar(nueva, anterior);
                        intercambio = true;
                    }     

                    // Si es posible realizar el movimiento, comprobamos si es un estado mejor
                    if(posible) {
                        // Si la caja ha sido movida, calculamos esa heuristica con la caja
                        if(nueva != nullptr) {
                            // Comprobamos que la caja que se haya movido es la del estado
                            if(caja -> fila == anterior.fila && caja -> columna == anterior.columna) {
                                heuNueva = heuristica(*nueva, *objetivo, estado, intercambio);
                            } else {
                                // Si se ha movido otra caja, se calcula con la caja seleccionada
                                heuNueva = heuristica(*caja, *objetivo, estado, intercambio);
                            }
                        } else {
                            heuNueva = heuristica(*caja, *objetivo, estado, intercambio);
                        }

                        // Si la heurística mejora, nos quedamos con este estado
                        if(heuNueva < heuMejor) {
                            // Borramos el mejor hasta ahora, ya que se ha mejorado.
                            if(estadoMejor != nullptr) {
                                delete estadoMejor;
                            }

                            if(nuevaMejor != nullptr) {
                                delete nuevaMejor;
                            }

                            estadoMejor = estado;
                            heuMejor = heuNueva;
                            anteriorMejor = anterior;
                            nuevaMejor = nueva;
                        } else {
                            // Si la heurística no mejora, desechamos los datos
                            delete estado;
                            delete nueva;
                        }
                    } else {
                        // Si no es posible el movimiento, borramos los datos
                        delete estado;
                        delete nueva;
                    }
                }
            }
        }

        // Tras comprobar todas las opciones, hacemos el mejor movimiento
        if(estadoMejor != nullptr) {
            this -> tablero = estadoMejor;
            heuActual = heuMejor;
            
            // Cambiamos las posiciones de las cajas en los vectores si se han movido
            if(nuevaMejor != nullptr) {
                bool encontrado = false;

                // Buscamos la caja en el vector de cajas
                for(auto it = cajas.begin(); it != cajas.end(); it++) {
                    if(it -> fila == anteriorMejor.fila &&
                       it -> columna == anteriorMejor.columna) {
                        // Si esa posicion se ha modificado, cambiamos la anterior posicion
                        *it = *nuevaMejor;
                        encontrado = true;
                    }
                }

                // Si no encontramos la caja en el vector de cajas esta ha sido 
                // colocada y ahora movida. Cambiamos su estado. La quitamos de 
                // las cajas colocadas y la pasamos a las cajas pendientes de colocar
                if(!encontrado) {
                    encontrado = false;
                    for(auto it = cajasDescolocadas.begin(); it != cajasDescolocadas.end(); it++) {
                        if(it -> fila == anteriorMejor.fila &&
                           it -> columna == anteriorMejor.columna) {
                            *it = *nuevaMejor;
                            encontrado = true;
                        }
                    }

                    // Si no está en cajasDecolocadas, lo borramos de cajasColocadas y lo insertamos
                    // Tambien cambiamos el objetivo usado por el objetivo cambiado
                    if(!encontrado) {
                        // Buscamos la caja colocada que se ha movido y la borramos
                        for(auto it = cajasColocadas.begin(); it != cajasColocadas.end(); it++) {
                            if(it -> fila == anteriorMejor.fila &&
                               it -> columna == anteriorMejor.columna) {
                                cajasColocadas.erase(it);
                                break;
                            }
                        }

                        // Buscamos el objetivo usado a la lista de cambiados
                        for(auto it = objetivosUsados.begin(); it != objetivosUsados.end(); it++) {
                            if(it -> fila == anteriorMejor.fila &&
                               it -> columna == anteriorMejor.columna) {
                                objetivosUsados.erase(it);
                                break;
                            }    
                        }

                        //Insertamos el objetivo borrado en los objetivos que han sido cambiados
                        objetivosCambiados.push_back(anteriorMejor);

                        // Insertamos la nueva posicion de la caja
                        cajasDescolocadas.push_back(*nueva);
                    }
                }
            }

            // Guardamos el movimiento realizado en el vector de movimientos
            if(tablero -> getMovimiento() != "") {
                movimientos.push_back(tablero -> getMovimiento());
            }

            // Reestablecemos los valores de mejor
            delete nuevaMejor;
            nuevaMejor = nullptr;
            estadoMejor = nullptr;
            movido = true;
        }

        // Comprobamos si alguna caja ha llegado a su objetivo
        // Si todas estan colocadas, hemos encontrado solución
        bool borrado = false;
        for(auto caja = cajas.begin(); caja != cajas.end() && !borrado; caja++) {
            for(auto objetivo = objetivos.begin(); objetivo != objetivos.end() && !borrado; objetivo++) {
                // Si la posicion de la caja y el objetivo son iguales
                // Esa caja se ha colocado. Borramos la caja y el objetivo de los disponibles
                if(caja -> fila == objetivo -> fila &&
                   caja -> columna == objetivo -> columna) {
                    objetivosUsados.push_back(*objetivo);
                    cajasColocadas.push_back(*caja);
                    cajas.erase(caja);
                    objetivos.erase(objetivo);

                    // Si se ha borrado una caja. Reseteamos la heurística
                    if(cajas.size() > 0 && objetivos.size() > 0) {
                        heuActual = heuristica(cajas[0], objetivos[0], this -> tablero, false);
                    } else {
                        heuActual = INT_MAX;
                    }
                    borrado = true;
                }
            }
        }
    
        // Comprobamos que estan todas las cajas colocadas
        if(cajas.size() == 0) {
            // Si no hay cajas por colocar y tampoco hay cajas que se
            // hayan movido estando colocadas -> terminamos
            if(cajasDescolocadas.size() == 0) {
                acabado = true;
            } else {
                // Intentamos colocar las cajas que se han movido estando colocadas
                for(auto caja = cajasDescolocadas.begin(); caja != cajasDescolocadas.end(); caja++) {
                    cajas.push_back(*caja);
                }

                for(auto objetivo = objetivosCambiados.begin(); objetivo != objetivosCambiados.end(); objetivo++) {
                    objetivos.push_back(*objetivo);
                }

                objetivosCambiados.clear();
                cajasDescolocadas.clear();
                heuActual = heuristica(cajas[0], objetivos[0], tablero, false);
            }
        }

        // Si no se ha hecho ningún movimiento, cortamos la ejecución
        if(!movido) {
            acabado = true;
        }

    }

    // Si en el último movimiento se ha movido, hemos encontrado solucion
    return movido;
}

Algoritmo::~Algoritmo() {
    Tablero* estado = tablero;
    Tablero* padre = tablero -> getPadre();
    
    while(padre != nullptr) {
        delete estado;
        estado = padre;
        padre = padre -> getPadre();
    }

    delete estado;
}