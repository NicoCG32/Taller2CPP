        // ==================== ZONA DE TESTEOS ====================
        
        // TEST 1: Matriz 2x2 * Matriz 2x2 (Caso básico)
        // Matriz 1 (2x2): [[3, 2],    Matriz 2 (2x2): [[5, 6],    
        //                  [1, 4]]                      [7, 8]]    
        // Multiplicación 1x2 (2x2 * 2x2 = 2x2): POSIBLE (columnas M1 = filas M2)
        //   Resultado: [[29, 34],     (3*5+2*7=29, 3*6+2*8=34, 1*5+4*7=33, 1*6+4*8=38)
        //               [33, 38]]
        // Multiplicación 2x1 (2x2 * 2x2 = 2x2): POSIBLE (columnas M2 = filas M1)
        //   Resultado: [[21, 34],     (5*3+6*1=21, 5*2+6*4=34, 7*3+8*1=29, 7*2+8*4=46)
        //               [29, 46]]

        /*
        principal->add(3, 0, 0);
        principal->add(2, 1, 0);
        principal->add(1, 0, 1);
        principal->add(4, 1, 1);

        second->add(5, 0, 0);
        second->add(6, 1, 0);
        second->add(7, 0, 1);
        second->add(8, 1, 1);
        */

        // TEST 2: Matriz 1x3 * Matriz 3x1 (Fila x Columna)
        // Matriz 1 (1x3): [[1, 2, 3]]    Matriz 2 (3x1): [[4],    
        //                                                  [5],
        //                                                  [6]]
        // Multiplicación 1x2 (1x3 * 3x1 = 1x1): POSIBLE (columnas M1 = filas M2 = 3)
        //   Resultado: [[32]]         (1*4+2*5+3*6=32)
        // Multiplicación 2x1 (3x1 * 1x3 = 3x3): POSIBLE (columnas M2 = filas M1 = 1)
        //   Resultado: [[4,  8,  12],
        //               [5,  10, 15],
        //               [6,  12, 18]]   (4*1=4, 4*2=8, 4*3=12; 5*1=5, 5*2=10, 5*3=15; 6*1=6, 6*2=12, 6*3=18)

        /*
        principal->add(1, 0, 0);
        principal->add(2, 1, 0);
        principal->add(3, 2, 0);
        
        second->add(4, 0, 0);
        second->add(5, 0, 1);
        second->add(6, 0, 2);
        */
        
        // TEST 3: Matriz 2x2 * Matriz 2x1 (Rectángulo x Columna) - CON EXPANSIÓN
        // Matriz 1 (2x2): [[3, 2],    Matriz 2 (2x1): [[5],    
        //                  [1, 4]]                      [0]]    
        // Multiplicación 1x2 (2x2 * 2x1 = 2x1): POSIBLE (columnas M1=2 = filas M2=2)
        //   Resultado: [[15],     (3*5+2*0=15, 1*5+4*0=5)
        //               [5]]
        // Multiplicación 2x1 (2x1 * 2x2): REQUIERE EXPANSIÓN (columnas M2=1 → se expande a 2)
        //   M1 se expande: [[3, 2],  →  [[3, 2],
        //                   [1, 4]]      [1, 4]]  (no cambia, ya tiene 2 filas)
        //   M2 se expande: [[5],     →  [[5, 0],
        //                   [0]]         [0, 0]]  (se agrega columna x=1 vacía)
        //   Resultado (2x2 * 2x2 = 2x2): [[15, 10],    (5*3+0*1=15, 5*2+0*4=10)
        //                                 [0,  0]]      (0*3+0*1=0,  0*2+0*4=0)
        //   NOTA: Solo se almacenan valores no-cero: (0,0)=15, (1,0)=10

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
        // Matriz 1 (Identidad 3x3): [[1, 0, 0],    Matriz 2 (3x3): [[7, 8, 9],    
        //                            [0, 1, 0],                     [4, 5, 6],
        //                            [0, 0, 1]]                     [1, 2, 3]]
        // Multiplicación 1x2 (3x3 * 3x3 = 3x3): POSIBLE (columnas M1=3 = filas M2=3)
        //   Resultado: [[7, 8, 9],     (Identidad deja M2 sin cambios)
        //               [4, 5, 6],
        //               [1, 2, 3]]
        // Multiplicación 2x1 (3x3 * 3x3 = 3x3): POSIBLE (columnas M2=3 = filas M1=3)
        //   Resultado: [[7, 8, 9],     (M2 * Identidad deja M2 sin cambios)
        //               [4, 5, 6],
        //               [1, 2, 3]]

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

        // TEST 6: Expansión automática - Matriz 1x3 * Matriz 2x2
        // Matriz 1 (1x3): [[2, 3, 5]]      Matriz 2 (2x2): [[6, 7],    
        //                                                    [8, 9]]
        // Multiplicación 1x2 (1x3 * 2x2): REQUIERE EXPANSIÓN (columnas M1=3, filas M2=2 → se expande a 3)
        //   M2 se expande: [[6, 7],  →  [[6, 7],
        //                   [8, 9]]      [8, 9],   (se agrega fila y=2 vacía)
        //                                [0, 0]]
        //   Resultado (1x3 * 3x2 = 1x2): [[36, 41]]    (2*6+3*8+5*0=36, 2*7+3*9+5*0=41)
        // Multiplicación 2x1 (2x2 * 1x3): REQUIERE EXPANSIÓN (columnas M2=2, filas M1=1 → se expande a 2)
        //   M1 se expande: [[2, 3, 5]]  →  [[2, 3, 5],
        //                                    [0, 0, 0]]  (se agrega fila y=1 vacía)
        //   Resultado (2x2 * 2x3 = 2x3): [[12, 18, 30],    (6*2+7*0=12, 6*3+7*0=18, 6*5+7*0=30)
        //                                 [16, 24, 40]]    (8*2+9*0=16, 8*3+9*0=24, 8*5+9*0=40)

        /*
        principal->add(2, 0, 0);
        principal->add(3, 1, 0);
        principal->add(5, 2, 0);
        
        second->add(6, 0, 0);
        second->add(7, 1, 0);
        second->add(8, 0, 1);
        second->add(9, 1, 1);
        */

        
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
        
        // ==================== FIN ZONA DE TESTEOS ====================

        cin >> opcion;
        opcion = 0;