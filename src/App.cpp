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
        // ==================== ZONA DE TESTEOS ====================
        
        // TEST 1: Matriz 2x2 * Matriz 2x2 (Caso básico)
        // Matriz 1 (2x2): [[3, 2],    Matriz 2 (2x2): [[5, 6],    
        //                  [1, 4]]                      [7, 8]]    
        // Multiplicación 1x2 (2x2 * 2x2 = 2x2): POSIBLE (columnas M1 = filas M2)
        //   Resultado: [[29, 34],     (3*5+2*7=29, 3*6+2*8=34, 1*5+4*7=33, 1*6+4*8=38)
        //               [33, 38]]
        // Multiplicación 2x1 (2x2 * 2x2 = 2x2): POSIBLE (columnas M2 = filas M1)
        //   Resultado: [[21, 46],     (5*3+6*1=21, 5*2+6*4=46, 7*3+8*1=29, 7*2+8*4=46)
        //               [29, 46]]
        
        principal->add(3, 0, 0);
        principal->add(2, 1, 0);
        principal->add(1, 0, 1);
        principal->add(4, 1, 1);

        second->add(5, 0, 0);
        second->add(6, 1, 0);
        second->add(7, 0, 1);
        second->add(8, 1, 1);


        // TEST 2: Matriz 1x3 * Matriz 3x1 (Fila x Columna)
        // Matriz 1 (1x3): [[1, 2, 3]]    Matriz 2 (3x1): [[4],    
        //                                                  [5],
        //                                                  [6]]
        // Multiplicación 1x2 (1x3 * 3x1 = 1x1): POSIBLE (columnas M1 = filas M2 = 3)
        //   Resultado: [[32]]         (1*4+2*5+3*6=32)
        // Multiplicación 2x1 (3x1 * 1x3 = 3x3): POSIBLE (columnas M2 = filas M1 = 1)
        //   Resultado: [[4,  5,  6],  (4*1=4, 5*1=5, 6*1=6, 4*2=8, 5*2=10, 6*2=12, 4*3=12, 5*3=15, 6*3=18)
        //               [8,  10, 12],
        //               [12, 15, 18]]

        /*
        principal->add(1, 0, 0);
        principal->add(2, 1, 0);
        principal->add(3, 2, 0);
        
        second->add(4, 0, 0);
        second->add(5, 0, 1);
        second->add(6, 0, 2);
        */
        
        // TEST 3: Matriz 2x2 * Matriz 2x1 (Rectángulo x Columna)
        // Matriz 1 (2x2): [[3, 2],    Matriz 2 (2x1): [[5],    
        //                  [1, 4]]                      [0]]    
        // Multiplicación 1x2 (2x2 * 2x1 = 2x1): POSIBLE (columnas M1=2 = filas M2=2)
        //   Resultado: [[15],     (3*5+2*0=15, 1*5+4*0=5)
        //               [5]]
        // Multiplicación 2x1 (2x1 * 2x2): IMPOSIBLE (columnas M2=1 ≠ filas M1=2)
        //   El programa debe mostrar error de dimensiones incompatibles

        /*
        principal->add(3, 0, 0);
        principal->add(2, 1, 0);
        principal->add(1, 0, 1);
        principal->add(4, 1, 1);
        
        second->add(5, 0, 0);
        */
        
        // TEST 4: Matriz 3x2 * Matriz 2x3 (Rectángulo)
        // Matriz 1 (3x2): [[1, 2],     Matriz 2 (2x3): [[7, 8, 9],      
        //                  [3, 4],                       [6, 5, 4]]    
        //                  [5, 6]]                                
        // Multiplicación 1x2 (3x2 * 2x3 = 3x3): POSIBLE (columnas M1=2 = filas M2=2)
        //   Resultado: [[19, 18, 17],   (1*7+2*6=19, 1*8+2*5=18, 1*9+2*4=17)
        //               [45, 44, 43],   (3*7+4*6=45, 3*8+4*5=44, 3*9+4*4=43)
        //               [71, 70, 69]]   (5*7+6*6=71, 5*8+6*5=70, 5*9+6*4=69)
        // Multiplicación 2x1 (2x3 * 3x2 = 2x2): POSIBLE (columnas M2=3 = filas M1=3)
        //   Resultado: [[76,  100],    (7*1+8*3+9*5=76, 7*2+8*4+9*6=100)
        //               [41,  56]]      (6*1+5*3+4*5=41, 6*2+5*4+4*6=56)

        /*
        principal->add(1, 0, 0);
        principal->add(2, 1, 0);
        principal->add(3, 0, 1);
        principal->add(4, 1, 1);
        principal->add(5, 0, 2);
        principal->add(6, 1, 2);
        
        second->add(7, 0, 0);
        second->add(8, 1, 0);
        second->add(9, 2, 0);
        second->add(6, 0, 1);
        second->add(5, 1, 1);
        second->add(4, 2, 1);
        */
        
        // TEST 5: Matriz identidad 3x3 * Matriz cualquiera 3x3
        // Matriz 1: [[1, 0, 0],    Matriz 2: [[7, 8, 9],    Resultado: [[7, 8, 9],
        //            [0, 1, 0],                [4, 5, 6],                [4, 5, 6],
        //            [0, 0, 1]]                [1, 2, 3]]                [1, 2, 3]]

        /*
        principal->add(1, 0, 0);
        principal->add(1, 1, 1);
        principal->add(1, 2, 2);
        
        second->add(7, 0, 0);
        second->add(8, 1, 0);
        second->add(9, 2, 0);
        second->add(4, 0, 1);
        second->add(5, 1, 1);
        second->add(6, 2, 1);
        second->add(1, 0, 2);
        second->add(2, 1, 2);
        second->add(3, 2, 2);
        */

        /*
        cout << "Matriz Principal:" << endl;
        principal->printStoredValues();
        cout << "\nMatriz Second:" << endl;
        second->printStoredValues();
        cout << "\n===========================================\n" << endl;
        
        cout << "Multiplicando Matriz Principal * Matriz Second..." << endl;
        SparseMatrix* resultado = principal->multiply(second);
        cout << "\nResultado de la multiplicacion:" << endl;
        resultado->printStoredValues();
        cout << "\n-------------------------------------------\n" << endl;
        cout << "Multiplicando Matriz Second * Matriz Principal..." << endl;
        SparseMatrix* resultado2 = second->multiply(principal);
        cout << "\nResultado de la multiplicacion:" << endl;
        resultado2->printStoredValues();

        cout << "===========================================\n" << endl;
        */
        // ==================== FIN ZONA DE TESTEOS ====================

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