#include <iostream>
#include "DemoVector.h"
#include "vector.h"

using namespace std;

void DemoVector() {
    // Crear vector con capacidad inicial de 5
    CVector<int> vector(5);
    vector.insert(100);
    vector.insert(200);
    vector.insert(300);

    cout << "\n=== Estado inicial del vector ===\n";
    cout << vector << endl;                 // TODO (Nivel 2) operator<<
    cout << "vector[0] = " << vector[0] << endl; // TODO (Nivel 1) operator[]

    // Probar modificación directa con []
    vector[1] = 555;  // cambio un valor usando el operador []
    cout << "Tras modificar vector[1] = 555: " << vector << endl;

    // Constructor por copia (Nivel 1)
    cout << "\n=== Prueba del constructor por copia ===\n";
    CVector<int> copia(vector);
    cout << "Copia creada: " << copia << endl;
    copia[0] = 999;
    cout << "Copia modificada: " << copia << endl;
    cout << "Vector original tras modificar la copia: " << vector << endl;

    // Constructor por movimiento (Nivel 2)
    cout << "\n=== Prueba del constructor por movimiento ===\n";
    CVector<int> movido(std::move(vector));
    cout << "Vector movido: " << movido << endl;
    cout << "Vector original tras move: " << vector << endl;

    // Insertar después del move para ver si sigue funcionando
    int nuevo = 42;
    movido.insert(nuevo);
    cout << "Movido tras insertar 42: " << movido << endl;
}
