#include "Algoritmo.h"

bool Nodo::operator == (const Nodo& other) {
    return *estado == *other.estado;
}

bool operator > (const Nodo& other, const Nodo& other1) {
    return other.heuristica > other1.heuristica;
}

Algoritmo::Algoritmo(int algoritmo) {
    this -> numNodos = 0;
    this -> tablero = new Tablero();
    this -> lanzarAlgoritmo(algoritmo);
}

Algoritmo::Algoritmo(int algoritmo, string fichero) {
    this -> numNodos = 0;
    this -> tablero = new Tablero(fichero);
    this -> lanzarAlgoritmo(algoritmo);
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
    } else if(algoritmo == 4) {
        solucion = aEstrella();
    }

    tiempoFinal = chrono::high_resolution_clock::now();
        
    // Mostramos si tiene solución
    if(solucion) {
        cout << "Se ha encontrado solucion" << endl;
    } else {
        cout << "No se ha encontrado solucion" << endl;
    }

    // Mostramos los datos relevantes
    cout << endl << "Tiempo empleado: " 
         << chrono::duration_cast<chrono::nanoseconds>(tiempoFinal - tiempoInicial).count() 
         << "ns." << endl
         << "Numero de nodos generados: " << numNodos << endl << endl;

    // Mostramos el tablero
    tablero -> mostrarTablero();
}

void Algoritmo::mostrarSolucion(Tablero* estado) {
    if(estado ->getPadre() != nullptr) {
        mostrarSolucion(estado -> getPadre());
        cout << estado -> getMovimiento() << ",";
    }
}