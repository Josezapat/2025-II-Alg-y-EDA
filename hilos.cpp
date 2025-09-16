#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "hilos.h"
#include "vector.h"

using namespace std;

mutex cout_mutex;

void DemoThreads() {
    const int num_threads = 3;
    
    vector<thread> threads;
    CVector<int> vect(10);

    {
        lock_guard<mutex> lock(cout_mutex);
        cout << "Iniciando " << num_threads << " hilos..." << endl;
    }

    // Crear y lanzar los threads directamente con emplace_back
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(func, i, std::ref(vect));
    }

    // Esperar a que todos los threads terminen
    for (auto &thr : threads) {
        thr.join();
    }

    {
        lock_guard<mutex> lock(cout_mutex);
        cout << "Todos los hilos han finalizado." << endl;
    }
}
