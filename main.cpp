#include <iostream>
#include <string>
#include "DemoVector.h"  // Prototipo: void DemoVector();
#include "hilos.h"       // Prototipo: void DemoThreads();
// "vector.h" no es necesario incluirlo aquí si ya lo incluye DemoVector.h

/*
  Revisado por:
   1. Ernesto Cuadros-Vargas
   2. Jharvy Jonas Cadillo Tarazona
   4. Héctor Bobbio Hermoza
   20. Ortiz Lozano Eric Hernan
   22. Chandler Steven Perez Cueva
*/

// Forma 1 de Compilar:
//   g++ -std=c++17 -Wall -Wextra -g -pthread -o main main.cpp DemoVector.cpp hilos.cpp
// Forma 2 (Makefile):
//   make

int main(int argc, char* argv[]) {
    try {
        std::cout << "Hello Alg y EDA-UNI\n";

        // Si se especifica un modo por argumentos, ejecuta solo ese.
        if (argc > 1) {
            const std::string mode = argv[1];
            if (mode == "vector") {
                DemoVector();
            } else if (mode == "threads") {
                DemoThreads();
            } else {
                std::cerr << "Uso: ./main [vector|threads]\n"
                          << "Sin argumentos, se ejecutan ambas demos.\n";
                DemoVector();
                DemoThreads();
            }
        } else {
            // Por defecto: corre ambas demos
            DemoVector();
            DemoThreads();
        }

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Excepción: " << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "Error desconocido.\n";
        return 1;
    }
}
