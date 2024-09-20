/*
 * Lanza la ejecución de todos los ficheros con todos 
 * los algortimos realizados en la clase Algoritmo.
 * 
 * @author Fernando Broncano Morgado
 * @author Juan Francisco García Hinojosa
 * @author Antonio Javier Hidalgo Fernández
 */

#include "Algoritmo.h"

int main() {
    string fichero = "entrada//SOKOBOTTO";

    for(int alg = 1; alg < 5; alg++) {
        cout << "############ ALGORITMO " << alg << " LANZADO ############" << endl;
        for(int fic = 1; fic <= 10; fic++){        
            cout << "-------------------------------------------" << endl;
        
            cout << "Fichero de prueba SOKOROBOTTO" << fic << endl;
            Algoritmo(alg, fichero + to_string(fic) + ".txt");

            cout << "-------------------------------------------" 
                 << endl << endl << endl;
                 
        }

        cout << "\n\n\n\n" << endl;
    }

    return 0;
}