#include "App.h"
#include <iostream>

#include <chrono>
using namespace std;
using namespace std::chrono;

// Constructor
App::App() {
    principal = nullptr;
    second = nullptr;
}

// Destructor
App::~App() {
    if (principal != nullptr) {
        delete principal;
    }
    if (second != nullptr) {
        delete second;
    }
}

// Función MAIN
int main() {
    App app;
    return app.main();
}

int App::main() {
    if (!iniciarMatriz()) {
        cout << "Error al iniciar las matrices." << endl;
        return -1;
    }

    cout << "=== PROYECTO MATRICES POCO POBLADAS ===" << endl << endl;

    int opcion;
    do {
        mostrarMenuPrincipal();
        cin >> opcion;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Intente de nuevo.\n";
            continue;
        }

        switch (opcion) {
            case 1:
                mostrarMenuMatriz(1);
                break;
                
            case 2:
                mostrarMenuMatriz(2);
                break;

            case 3: {
                cout << "\n--- MULTIPLICAR MATRIZ PRINCIPAL * MATRIZ SECOND ---" << endl;
                auto inicio = high_resolution_clock::now();
                SparseMatrix* resultado = principal->multiply(second);
                auto fin = high_resolution_clock::now();
                
                auto tiempo = duration_cast<nanoseconds>(fin - inicio).count();
                
                if (resultado != nullptr) {
                    cout << "\nMatriz Resultante:" << endl;
                    resultado->printStoredValues();
                    cout << "\nTiempo de ejecucion: " << tiempo << " nanosegundos" << endl;
                    
                    guardarResultadoMultiplicacion(resultado);
                } else {
                    cout << "No se pudo realizar la multiplicacion.\n";
                    cout << "\nTiempo de ejecucion: " << tiempo << " nanosegundos" << endl;
                }
                break;
            }

            case 4: {
                cout << "\n--- MULTIPLICAR MATRIZ SECOND * MATRIZ PRINCIPAL ---" << endl;
                auto inicio = high_resolution_clock::now();
                SparseMatrix* resultado = second->multiply(principal);
                auto fin = high_resolution_clock::now();
                
                auto tiempo = duration_cast<nanoseconds>(fin - inicio).count();
                
                if (resultado != nullptr) {
                    cout << "\nMatriz Resultante:" << endl;
                    resultado->printStoredValues();
                    cout << "\nTiempo de ejecucion: " << tiempo << " nanosegundos" << endl;
                    
                    guardarResultadoMultiplicacion(resultado);
                } else {
                    cout << "No se pudo realizar la multiplicacion.\n";
                    cout << "\nTiempo de ejecucion: " << tiempo << " nanosegundos" << endl;
                }
                
                break;
            }

            case 0:
                cout << "\nSaliendo del programa..." << endl;
                break;
            
            default:
                cout << "\nOpcion invalida. Intente de nuevo." << endl;
        }

    } while (opcion != 0);

    return 0;
}

bool App::iniciarMatriz() {
    principal = new SparseMatrix();
    second = new SparseMatrix();
    return true;
}

void App::mostrarMenuPrincipal() {
    cout << "\n========================================" << endl;
    cout << "        MENU PRINCIPAL" << endl;
    cout << "========================================" << endl;
    cout << "1. Trabajar con Matriz 1" << endl;
    cout << "2. Trabajar con Matriz 2" << endl;
    cout << "3. Multiplicar Matriz 1 * Matriz 2" << endl;
    cout << "4. Multiplicar Matriz 2 * Matriz 1" << endl;
    cout << "0. Salir" << endl;
    cout << "========================================" << endl;
    cout << "Ingrese su opcion: ";
}

void App::mostrarMenuMatriz(int numeroMatriz) {
    int opcion;
    do {
        cout << "\n========================================" << endl;
        cout << "        MENU MATRIZ " << numeroMatriz << endl;
        cout << "========================================" << endl;
        cout << "1. Agregar elemento" << endl;
        cout << "2. Obtener elemento" << endl;
        cout << "3. Eliminar elemento" << endl;
        cout << "4. Mostrar matriz" << endl;
        cout << "5. Calcular densidad" << endl;
        cout << "6. Limpiar matriz" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "========================================" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Intente de nuevo.\n";
            continue;
        }

        procesarOpcionMatriz(opcion, numeroMatriz);

    } while (opcion != 0);
}

void App::procesarOpcionMatriz(int opcion, int numeroMatriz) {
    SparseMatrix* matrizActual = (numeroMatriz == 1) ? principal : second;
    
    long long tiempo;
    int valor, x, y;

    switch (opcion) {
        case 1: {
            cout << "\n--- AGREGAR ELEMENTO ---" << endl;
            cout << "Ingrese el valor: ";
            cin >> valor;
            cout << "Ingrese la columna (X): ";
            cin >> x;
            cout << "Ingrese la fila (Y): ";
            cin >> y;
            
            auto inicio = high_resolution_clock::now();
            matrizActual->add(valor, x, y);
            auto fin = high_resolution_clock::now();
            
            tiempo = duration_cast<nanoseconds>(fin - inicio).count();
            cout << "\nTiempo de ejecucion: " << tiempo << " nanosegundos" << endl;
            break;
        }
        case 2: {
            cout << "\n--- OBTENER ELEMENTO ---" << endl;
            cout << "Ingrese la columna (X): ";
            cin >> x;
            cout << "Ingrese la fila (Y): ";
            cin >> y;
            
            auto inicio = high_resolution_clock::now();
            valor = matrizActual->get(x, y);
            auto fin = high_resolution_clock::now();
            
            if (valor != INT32_MAX && valor != 0) {
                cout << "Valor en (" << x << "," << y << "): " << valor << endl;
            }
            
            tiempo = duration_cast<nanoseconds>(fin - inicio).count();
            cout << "\nTiempo de ejecucion: " << tiempo << " nanosegundos" << endl;
            break;
        }
        case 3: {
            cout << "\n--- ELIMINAR ELEMENTO ---" << endl;
            cout << "Ingrese la columna (X): ";
            cin >> x;
            cout << "Ingrese la fila (Y): ";
            cin >> y;
            
            auto inicio = high_resolution_clock::now();
            matrizActual->remove(x, y);
            auto fin = high_resolution_clock::now();
            
            tiempo = duration_cast<nanoseconds>(fin - inicio).count();
            cout << "\nTiempo de ejecucion: " << tiempo << " nanosegundos" << endl;
            break;
        }
        case 4: {
            cout << "\n--- MATRIZ " << numeroMatriz << " ---" << endl;
            
            auto inicio = high_resolution_clock::now();
            matrizActual->printStoredValues();
            auto fin = high_resolution_clock::now();
            
            tiempo = duration_cast<nanoseconds>(fin - inicio).count();
            cout << "\nTiempo de ejecucion: " << tiempo << " nanosegundos" << endl;
            break;
        }
        case 5: {
            cout << "\n--- DENSIDAD DE LA MATRIZ " << numeroMatriz << " ---" << endl;
            
            auto inicio = high_resolution_clock::now();
            int densidad = matrizActual->density();
            auto fin = high_resolution_clock::now();
            
            cout << "Densidad: " << densidad << "%" << endl;
            
            tiempo = duration_cast<nanoseconds>(fin - inicio).count();
            cout << "\nTiempo de ejecucion: " << tiempo << " nanosegundos" << endl;
            break;
        }
        case 6: {
            cout << "\n--- LIMPIAR MATRIZ " << numeroMatriz << " ---" << endl;
            
            if (numeroMatriz == 1) {
                delete principal;
                principal = new SparseMatrix();
            } else {
                delete second;
                second = new SparseMatrix();
            }
            
            cout << "Matriz " << numeroMatriz << " limpiada exitosamente." << endl;
            break;
        }
        case 0:
            cout << "\nVolviendo al menu principal..." << endl;
            break;
        default:
            cout << "\nOpcion invalida. Intente de nuevo." << endl;
    }
}

void App::guardarResultadoMultiplicacion(SparseMatrix* resultado) {
    cout << "\n¿Desea guardar el resultado? (1: Si, 0: No): ";
    int opcionGuardar;
    cin >> opcionGuardar;

    if (opcionGuardar == 1) {
        cout << "¿Sobreescribir Matriz Principal (1) o Matriz Second (2)? ";
        int matrizDestino;
        cin >> matrizDestino;
        if (matrizDestino == 1) {
            delete principal;
            principal = resultado;
            cout << "Matriz Principal actualizada con el resultado." << endl;
        } else if (matrizDestino == 2) {
            delete second;
            second = resultado;
            cout << "Matriz Second actualizada con el resultado." << endl;
        } else {
            cout << "Opcion invalida. Resultado no guardado." << endl;
            delete resultado;
        }
    } else {
        delete resultado;
    }
}