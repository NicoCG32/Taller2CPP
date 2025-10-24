#include "App.h"
#include <iostream>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

// Para la generación de matrices aleatorias
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <unordered_set>

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

void App::limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void App::mostrarEstadoMatrices() {
    cout << "=== PROYECTO MATRICES POCO POBLADAS ===" << endl;
    cout << "\n--- MATRIZ PRINCIPAL ---" << endl;
    if (principal != nullptr) {
        principal->printMatrix();
    } else {
        cout << "No inicializada" << endl;
    }
    
    cout << "\n--- MATRIZ SECOND ---" << endl;
    if (second != nullptr) {
        second->printMatrix();
    } else {
        cout << "No inicializada" << endl;
    }
    cout << endl;
}

int App::main() {
    if (!iniciarMatriz()) {
        cout << "Error al iniciar las matrices." << endl;
        return -1;
    }

    limpiarPantalla();
    mostrarEstadoMatrices();

    int opcion;
    do {
        mostrarMenuPrincipal();
        cin >> opcion;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            limpiarPantalla();
            mostrarEstadoMatrices();
            cout << "Entrada invalida. Intente de nuevo.\n";
            continue;
        }

        switch (opcion) {
            case 1: {
                int opcionManual;
                do {
                    limpiarPantalla();
                    mostrarEstadoMatrices();
                    mostrarMenuManual();
                    cin >> opcionManual;
                    
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Entrada invalida. Intente de nuevo.\n";
                        continue;
                    }

                    switch (opcionManual) {
                        case 1:
                            mostrarMenuMatriz(1);
                            break;
                            
                        case 2:
                            mostrarMenuMatriz(2);
                            break;

                        case 3: {
                            limpiarPantalla();
                            mostrarEstadoMatrices();
                            cout << "\n--- MULTIPLICAR MATRIZ 1 * MATRIZ 2 ---" << endl;
                            auto inicio = steady_clock::now();
                            SparseMatrix* resultado = principal->multiply(second);
                            auto fin = steady_clock::now();
                            
                            auto tiempoPs = duration_cast<std::chrono::duration<long long, std::pico>>(fin - inicio).count();
                            auto tiempoNs = duration_cast<nanoseconds>(fin - inicio).count();
                            auto tiempoMs = duration_cast<milliseconds>(fin - inicio).count();
                            
                            if (resultado != nullptr) {
                                cout << "\nMatriz Resultante:" << endl;
                                resultado->printStoredValues();
                                cout << "\nTiempo de ejecucion: " << tiempoMs << " ms, " << tiempoNs << " ns, " << tiempoPs << " ps" << endl;
                                
                                guardarResultado(resultado);
                            } else {
                                cout << "No se pudo realizar la multiplicacion.\n";
                                cout << "\nTiempo de ejecucion: " << tiempoMs << " ms, " << tiempoNs << " ns, " << tiempoPs << " ps" << endl;
                            }
                            cout << "\nPresione Enter para continuar...";
                            cin.ignore();
                            cin.get();
                            break;
                        }

                        case 4: {
                            limpiarPantalla();
                            mostrarEstadoMatrices();
                            cout << "\n--- MULTIPLICAR MATRIZ 2 * MATRIZ 1 ---" << endl;
                            auto inicio = steady_clock::now();
                            SparseMatrix* resultado = second->multiply(principal);
                            auto fin = steady_clock::now();
                            
                            auto tiempoPs = duration_cast<std::chrono::duration<long long, std::pico>>(fin - inicio).count();
                            auto tiempoNs = duration_cast<nanoseconds>(fin - inicio).count();
                            auto tiempoMs = duration_cast<milliseconds>(fin - inicio).count();
                            
                            if (resultado != nullptr) {
                                cout << "\nMatriz Resultante:" << endl;
                                resultado->printStoredValues();
                                cout << "\nTiempo de ejecucion: " << tiempoMs << " ms, " << tiempoNs << " ns, " << tiempoPs << " ps" << endl;
                                
                                guardarResultado(resultado);
                            } else {
                                cout << "No se pudo realizar la multiplicacion.\n";
                                cout << "\nTiempo de ejecucion: " << tiempoMs << " ms, " << tiempoNs << " ns, " << tiempoPs << " ps" << endl;
                            }
                            
                            cout << "\nPresione Enter para continuar...";
                            cin.ignore();
                            cin.get();
                            break;
                        }

                        case 0:
                            cout << "\nVolviendo al menu principal..." << endl;
                            break;
                        
                        default:
                            cout << "\nOpcion invalida. Intente de nuevo." << endl;
                    }

                } while (opcionManual != 0);
                limpiarPantalla();
                mostrarEstadoMatrices();
                break;
            }
                
            case 2: { // MODO PRUEBAS, ESTO SE HIZO CON AYUDA DE CHATGPT
                while (true) {
                    limpiarPantalla();
                    mostrarEstadoMatrices();
                    mostrarMenuPruebas();

                    cout << "Ingrese su opcion: ";
                    int opcionPrueba;
                    cin >> opcionPrueba;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        continue;
                    }

                    if (opcionPrueba == 0) {
                        cout << "\nVolviendo al menu principal..." << endl;
                        break;
                    }

                    if (opcionPrueba == 1) {
                        // Generar matriz (flujo previo)
                        cout << "\nSeleccione cantidad de datos:" << endl;
                        cout << "1. 50 datos" << endl;
                        cout << "2. 250 datos" << endl;
                        cout << "3. 500 datos" << endl;
                        cout << "4. 1000 datos" << endl;
                        cout << "5. 5000 datos" << endl;
                        cout << "Opcion: ";
                        int opcionDatos;
                        cin >> opcionDatos;
                        int cantidadDatos = 0;
                        switch (opcionDatos) {
                            case 1: cantidadDatos = 50; break;
                            case 2: cantidadDatos = 250; break;
                            case 3: cantidadDatos = 500; break;
                            case 4: cantidadDatos = 1000; break;
                            case 5: cantidadDatos = 5000; break;
                            default: cout << "Opcion invalida." << endl; continue;
                        }
                        cout << "\nSeleccione densidad objetivo:" << endl;
                        cout << "1. Baja densidad (<40%)" << endl;
                        cout << "2. Alta densidad (>70%)" << endl;
                        cout << "Opcion: ";
                        int opcionDensidad;
                        cin >> opcionDensidad;
                        int densidadObjetivo;
                        if (opcionDensidad == 1) densidadObjetivo = 30;
                        else if (opcionDensidad == 2) densidadObjetivo = 75;
                        else { cout << "Opcion invalida." << endl; continue; }

                        SparseMatrix* temp = new SparseMatrix();
                        auto inicio = steady_clock::now();
                        generarMatrizAleatoria(temp, cantidadDatos, densidadObjetivo);
                        auto fin = steady_clock::now();
                        auto tiempoPs = duration_cast<std::chrono::duration<long long, std::pico>>(fin - inicio).count();
                        auto tiempoNs = duration_cast<nanoseconds>(fin - inicio).count();
                        auto tiempoMs = duration_cast<milliseconds>(fin - inicio).count();
                        cout << "Tiempo de generacion: " << tiempoMs << " ms, " << tiempoNs << " ns, " << tiempoPs << " ps" << endl;

                        // Tiempo densidad
                        auto inicioDensidad = steady_clock::now();
                        int densidadReal = temp->density();
                        auto finDensidad = steady_clock::now();
                        auto tiempoDensidadPs = duration_cast<std::chrono::duration<long long, std::pico>>(finDensidad - inicioDensidad).count();
                        auto tiempoDensidadNs = duration_cast<nanoseconds>(finDensidad - inicioDensidad).count();
                        auto tiempoDensidadMs = duration_cast<milliseconds>(finDensidad - inicioDensidad).count();
                        cout << "Densidad real: " << densidadReal << "%" << endl;
                        cout << "Tiempo de calculo de densidad: " << tiempoDensidadMs << " ms, " << tiempoDensidadNs << " ns, " << tiempoDensidadPs << " ps" << endl;

                        guardarResultado(temp);
                        cout << "\nPresione Enter para continuar...";
                        cin.ignore();
                        cin.get();
                    } else if (opcionPrueba == 2) {
                        // Probar add: matriz vacia + coordenadas fijas en cada iteracion
                        cout << "\n¿Cuantas inserciones por repeticion (m)? ";
                        int m;
                        cin >> m;
                        if (m <= 0) { cout << "m debe ser > 0" << endl; continue; }
                        
                        // Generar m coordenadas unicas fijas (fuera del cronometro)
                        vector<int> xs; xs.reserve(m);
                        vector<int> ys; ys.reserve(m);
                        vector<int> vs; vs.reserve(m);
                        unordered_set<long long> used; used.reserve(m * 2);
                        auto key = [](int x, int y) {
                            return (static_cast<long long>(static_cast<unsigned int>(y)) << 32) |
                                   static_cast<unsigned int>(x);
                        };
                        int W = 100; int H = 100; // espacio de coordenadas
                        while (static_cast<int>(xs.size()) < m) {
                            int x = rand() % W;
                            int y = rand() % H;
                            long long k = key(x, y);
                            if (used.find(k) == used.end()) {
                                int v = (rand() % 200) - 100; if (v == 0) v = 1;
                                used.insert(k);
                                xs.push_back(x);
                                ys.push_back(y);
                                vs.push_back(v);
                            }
                        }
                        
                        // Warmup: 2 repeticiones (matriz vacia + m inserciones)
                        const int warmup = 2;
                        for (int w = 0; w < warmup; ++w) {
                            SparseMatrix* tempW = new SparseMatrix();
                            for (int i = 0; i < m; ++i) {
                                tempW->add(vs[i], xs[i], ys[i]);
                            }
                            delete tempW;
                        }
                        
                        // Auto-calibrar: repetir hasta acumular >= 10 ms
                        long long totalPsAccum = 0;
                        long long totalNsAccum = 0;
                        long long totalMsAccum = 0;
                        long long totalCalls = 0;
                        int blocks = 0;
                        const int maxBlocks = 10000;
                        while (totalMsAccum < 10 && blocks < maxBlocks) {
                            SparseMatrix* temp = new SparseMatrix();
                            auto t0 = steady_clock::now();
                            for (int i = 0; i < m; ++i) {
                                temp->add(vs[i], xs[i], ys[i]);
                            }
                            auto t1 = steady_clock::now();
                            delete temp;
                            long long ps = duration_cast<std::chrono::duration<long long, std::pico>>(t1 - t0).count();
                            long long ns = duration_cast<nanoseconds>(t1 - t0).count();
                            long long ms = duration_cast<milliseconds>(t1 - t0).count();
                            totalPsAccum += ps;
                            totalNsAccum += ns;
                            totalMsAccum += ms;
                            totalCalls += m;
                            ++blocks;
                        }

                        // Promedios como double para evitar truncamientos a 0
                        double avgNs = (totalCalls > 0) ? (static_cast<double>(totalNsAccum) / totalCalls) : 0.0;
                        double avgMs = avgNs / 1e6;
                        double avgPs = (totalCalls > 0) ? (static_cast<double>(totalPsAccum) / totalCalls) : 0.0;
                        cout << "\n========== RESULTADOS ADD ==========" << endl;
                        cout << "Iteraciones: " << totalCalls << endl;
                        cout << "Tiempo total: " << totalMsAccum << " ms" << endl;
                        cout << fixed << setprecision(6);
                        cout << "Promedio: " << avgMs << " ms" << endl;
                        cout << "Promedio: " << avgNs << " ns" << endl;
                        cout << "Promedio: " << avgPs << " ps" << endl;
                        cout << "====================================" << endl;
                        cout << "\nPresione Enter para continuar...";
                        cin.ignore();
                        cin.get();
                    } else if (opcionPrueba == 3) {
                        // Probar get: matriz base fija + set de consultas fijas
                        cout << "\nProbar get sobre: 1) Matriz Principal  2) Matriz Second\nOpcion: ";
                        int sel; cin >> sel;
                        SparseMatrix* base = (sel == 2 ? second : principal);
                        if (!base) { cout << "Matriz no disponible." << endl; continue; }
                        

                        int n = base->countNonZero();
                        
                        // Generar n coordenadas de consulta fijas (fuera del cronometro)
                        vector<int> xs; xs.reserve(n);
                        vector<int> ys; ys.reserve(n);
                        int width = base->getWidth();
                        int height = base->getHeight();
                        if (width <= 0) width = 1;
                        if (height <= 0) height = 1;
                        for (int i = 0; i < n; ++i) {
                            xs.push_back(rand() % width);
                            ys.push_back(rand() % height);
                        }
                        
                        // Warmup: 2 repeticiones
                        const int warmup = 2;
                        for (int w = 0; w < warmup; ++w) {
                            for (int i = 0; i < n; ++i) {
                                volatile int dummy = base->get(xs[i], ys[i]);
                                (void)dummy;
                            }
                        }
                        
                        // Auto-calibrar: repetir hasta acumular >= 10 ms
                        long long totalPsAccum = 0;
                        long long totalNsAccum = 0;
                        long long totalMsAccum = 0;
                        long long totalCalls = 0;
                        int blocks = 0;
                        const int maxBlocks = 1000000;
                        while (totalMsAccum < 10 && blocks < maxBlocks) {
                            auto t0 = steady_clock::now();
                            for (int i = 0; i < n; ++i) {
                                volatile int val = base->get(xs[i], ys[i]);
                                (void)val;
                            }
                            auto t1 = steady_clock::now();
                            long long ps = duration_cast<std::chrono::duration<long long, std::pico>>(t1 - t0).count();
                            long long ns = duration_cast<nanoseconds>(t1 - t0).count();
                            long long ms = duration_cast<milliseconds>(t1 - t0).count();
                            totalPsAccum += ps;
                            totalNsAccum += ns;
                            totalMsAccum += ms;
                            totalCalls += n;
                            ++blocks;
                        }
                        // Promedios como double para evitar truncamientos a 0
                        double avgNs = (totalCalls > 0) ? (static_cast<double>(totalNsAccum) / totalCalls) : 0.0;
                        double avgMs = avgNs / 1e6;
                        double avgPs = (totalCalls > 0) ? (static_cast<double>(totalPsAccum) / totalCalls) : 0.0;
                        cout << "\n========== RESULTADOS GET ==========" << endl;
                        cout << "Iteraciones: " << totalCalls << endl;
                        cout << "Tiempo total: " << totalMsAccum << " ms" << endl;
                        cout << fixed << setprecision(6);
                        cout << "Promedio: " << avgMs << " ms" << endl;
                        cout << "Promedio: " << avgNs << " ns" << endl;
                        cout << "Promedio: " << avgPs << " ps" << endl;
                        cout << "====================================" << endl;
                        cout << "\nPresione Enter para continuar...";
                        cin.ignore();
                        cin.get();
                    } else if (opcionPrueba == 4) {
                        // Probar multiply: misma A (base) y B fijas, medir solo multiply()
                        cout << "\nUsar como A (base): 1) Matriz Principal  2) Matriz Second\nOpcion: ";
                        int selA; cin >> selA;
                        SparseMatrix* A = (selA == 2 ? second : principal);
                        if (!A) { cout << "Matriz A no disponible." << endl; continue; }

                        // Crear B una vez fuera del cronometro
                        int cantidadDatos = A->countNonZero();
                        int densidadClase;
                        {
                            int d = A->density();
                            densidadClase = (d >= 70 ? 75 : 30);
                        }
                        SparseMatrix* B = new SparseMatrix();
                        generarMatrizAleatoria(B, cantidadDatos, densidadClase);
                        
                        // Warmup: 2 repeticiones
                        const int warmup = 2;
                        for (int w = 0; w < warmup; ++w) {
                            SparseMatrix* resWarm = A->multiply(B);
                            delete resWarm;
                        }
                        
                        // Medir 10 repeticiones
                        const int repeticiones = 10;
                        long long totalPsAccum = 0;
                        long long totalNsAccum = 0;
                        long long totalMsAccum = 0;
                        for (int r = 0; r < repeticiones; ++r) {
                            auto t0 = steady_clock::now();
                            SparseMatrix* res = A->multiply(B);
                            auto t1 = steady_clock::now();
                            delete res;
                            long long ps = duration_cast<std::chrono::duration<long long, std::pico>>(t1 - t0).count();
                            long long ns = duration_cast<nanoseconds>(t1 - t0).count();
                            long long ms = duration_cast<milliseconds>(t1 - t0).count();
                            totalPsAccum += ps;
                            totalNsAccum += ns;
                            totalMsAccum += ms;
                        }
                        delete B;
                        
                        // Promedios como double
                        double avgNs = (repeticiones > 0) ? (static_cast<double>(totalNsAccum) / repeticiones) : 0.0;
                        double avgMs = avgNs / 1e6;
                        double avgPs = (repeticiones > 0) ? (static_cast<double>(totalPsAccum) / repeticiones) : 0.0;
                        
                        cout << "\n======== RESULTADOS MULTIPLY =======" << endl;
                        cout << "Iteraciones: " << repeticiones << endl;
                        cout << "Tiempo total: " << totalMsAccum << " ms" << endl;
                        cout << fixed << setprecision(6);
                        cout << "Promedio: " << avgMs << " ms" << endl;
                        cout << "Promedio: " << avgNs << " ns" << endl;
                        cout << "Promedio: " << avgPs << " ps" << endl;
                        cout << "====================================" << endl;
                        cout << "\nPresione Enter para continuar...";
                        cin.ignore();
                        cin.get();
                    } else {
                        cout << "Opcion invalida." << endl;
                    }
                }
                limpiarPantalla();
                mostrarEstadoMatrices();
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
    cout << "1. Modo MANUAL" << endl;
    cout << "2. Modo TESTEO" << endl;
    cout << "0. Salir" << endl;
    cout << "========================================" << endl;
    cout << "Ingrese su opcion: ";
}

void App::mostrarMenuManual() {
    cout << "\n========================================" << endl;
    cout << "        MENU MODO MANUAL" << endl;
    cout << "========================================" << endl;
    cout << "1. Trabajar con Matriz 1" << endl;
    cout << "2. Trabajar con Matriz 2" << endl;
    cout << "3. Multiplicar Matriz 1 * Matriz 2" << endl;
    cout << "4. Multiplicar Matriz 2 * Matriz 1" << endl;
    cout << "0. Volver al menu principal" << endl;
    cout << "========================================" << endl;
    cout << "Ingrese su opcion: ";
}

void App::mostrarMenuPruebas() {
    cout << "\n========================================" << endl;
    cout << "        MENU MODO PRUEBAS" << endl;
    cout << "========================================" << endl;
    cout << "Seleccione una opcion de prueba" << endl;
    cout << "1. Generar matriz" << endl;
    cout << "2. Probar add" << endl;
    cout << "3. Probar get" << endl;
    cout << "4. Probar multiply" << endl;
    cout << "0. Volver al menu principal" << endl;
    cout << "========================================" << endl;
}

void App::mostrarMenuMatriz(int numeroMatriz) {
    int opcion;
    do {
        limpiarPantalla();
        mostrarEstadoMatrices();
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
    
    long long tiempoPs, tiempoNs, tiempoMs;
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
            
            auto inicio = steady_clock::now();
            matrizActual->add(valor, x, y);
            auto fin = steady_clock::now();
            
            tiempoPs = duration_cast<std::chrono::duration<long long, std::pico>>(fin - inicio).count();
            tiempoNs = duration_cast<nanoseconds>(fin - inicio).count();
            tiempoMs = duration_cast<milliseconds>(fin - inicio).count();
            cout << "\nTiempo de ejecucion: " << tiempoMs << " ms, " << tiempoNs << " ns, " << tiempoPs << " ps" << endl;
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        }
        case 2: {
            cout << "\n--- OBTENER ELEMENTO ---" << endl;
            cout << "Ingrese la columna (X): ";
            cin >> x;
            cout << "Ingrese la fila (Y): ";
            cin >> y;
            
            auto inicio = steady_clock::now();
            valor = matrizActual->get(x, y);
            auto fin = steady_clock::now();
            
            if (valor != 0) {
                cout << "Valor en (" << x << "," << y << "): " << valor << endl;
            }
            
            tiempoPs = duration_cast<std::chrono::duration<long long, std::pico>>(fin - inicio).count();
            tiempoNs = duration_cast<nanoseconds>(fin - inicio).count();
            tiempoMs = duration_cast<milliseconds>(fin - inicio).count();
            cout << "\nTiempo de ejecucion: " << tiempoMs << " ms, " << tiempoNs << " ns, " << tiempoPs << " ps" << endl;
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        }
        case 3: {
            cout << "\n--- ELIMINAR ELEMENTO ---" << endl;
            cout << "Ingrese la columna (X): ";
            cin >> x;
            cout << "Ingrese la fila (Y): ";
            cin >> y;
            
            auto inicio = steady_clock::now();
            matrizActual->remove(x, y);
            auto fin = steady_clock::now();
            
            tiempoPs = duration_cast<std::chrono::duration<long long, std::pico>>(fin - inicio).count();
            tiempoNs = duration_cast<nanoseconds>(fin - inicio).count();
            tiempoMs = duration_cast<milliseconds>(fin - inicio).count();
            cout << "\nTiempo de ejecucion: " << tiempoMs << " ms, " << tiempoNs << " ns, " << tiempoPs << " ps" << endl;
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        }
        case 4: {
            cout << "\n--- MATRIZ " << numeroMatriz << " ---" << endl;
            
            auto inicio = steady_clock::now();
            matrizActual->printStoredValues();
            auto fin = steady_clock::now();
            
            tiempoPs = duration_cast<std::chrono::duration<long long, std::pico>>(fin - inicio).count();
            tiempoNs = duration_cast<nanoseconds>(fin - inicio).count();
            tiempoMs = duration_cast<milliseconds>(fin - inicio).count();
            cout << "\nTiempo de ejecucion: " << tiempoMs << " ms, " << tiempoNs << " ns, " << tiempoPs << " ps" << endl;
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        }
        case 5: {
            cout << "\n--- DENSIDAD DE LA MATRIZ " << numeroMatriz << " ---" << endl;
            
            auto inicio = steady_clock::now();
            int densidad = matrizActual->density();
            auto fin = steady_clock::now();
            
            cout << "Densidad: " << densidad << "%" << endl;
            
            tiempoPs = duration_cast<std::chrono::duration<long long, std::pico>>(fin - inicio).count();
            tiempoNs = duration_cast<nanoseconds>(fin - inicio).count();
            tiempoMs = duration_cast<milliseconds>(fin - inicio).count();
            cout << "\nTiempo de ejecucion: " << tiempoMs << " ms, " << tiempoNs << " ns, " << tiempoPs << " ps" << endl;
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
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
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        }
        case 0:
            cout << "\nVolviendo al menu principal..." << endl;
            break;
        default:
            cout << "\nOpcion invalida. Intente de nuevo." << endl;
    }
}

void App::guardarResultado(SparseMatrix* resultado) {
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

void App::generarMatrizAleatoria(SparseMatrix* matriz, int cantidadDatos, int densidadObjetivo) {
    srand(static_cast<unsigned>(time(nullptr)));

    int filas = 0, columnas = 0;
    if (densidadObjetivo >= 70) {

        // Alta densidad
        const int minPercent = 71;
        int maxCeldas = (cantidadDatos * 100) / minPercent;
        if (maxCeldas < cantidadDatos) maxCeldas = cantidadDatos;

        int lado = static_cast<int>(sqrt(maxCeldas));
        if (lado == 0) lado = 1;
        filas = lado;
        columnas = maxCeldas / filas;
        if (columnas == 0) columnas = 1;

        // Asegurar que haya capacidad suficiente para todos los datos
        while (filas * columnas < cantidadDatos) {
            columnas++;
        }
        // Mantener área lo más pequeña posible (densidad alta)
        while ((filas + 1) * columnas <= maxCeldas) {
            filas++;
        }
        while (filas * (columnas + 1) <= maxCeldas) {
            columnas++;
        }
    } else {
        // Baja densidad
        const int maxPercent = 39;
        int minCeldas = (cantidadDatos * 100 + maxPercent - 1) / maxPercent;
        if (minCeldas < cantidadDatos) minCeldas = cantidadDatos;

        int lado = static_cast<int>(sqrt(minCeldas));
        if (lado == 0) lado = 1;
        filas = lado;

        columnas = (minCeldas + filas - 1) / filas;
        while ((filas + 1) * columnas <= minCeldas) {
            filas++;
        }
    }

    cout << "\nGenerando matriz de aproximadamente " << filas << "x" << columnas
         << " con " << cantidadDatos << " valores no-cero..." << endl;

    // Evitar duplicados
    const int totalCeldas = filas * columnas;
    std::vector<char> ocupado(totalCeldas, 0);

    auto idx = [columnas](int x, int y) { return y * columnas + x; };

    int insertados = 0;
    int intentos = 0;
    int maxIntentos = cantidadDatos * 20;

    while (insertados < cantidadDatos && intentos < maxIntentos) {
        int x = rand() % columnas;
        int y = rand() % filas;
        int i = idx(x, y);
        if (!ocupado[i]) {
            // Generar valor aleatorio no-cero
            int value = (rand() % 200) - 100;
            if (value == 0) value = 1;

            matriz->add(value, x, y);
            ocupado[i] = 1;
            insertados++;
        }
        intentos++;
    }

    cout << "Matriz generada." << endl;
}

