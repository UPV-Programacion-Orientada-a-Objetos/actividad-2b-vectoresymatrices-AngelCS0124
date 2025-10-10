#include <iostream>
#include <string>

// Prototipos de funciones
int imprimirMenu();
void imprimirMensaje(std::string tipo, std::string mensaje);
bool validarEntradaNumerica(int &entrada);
void inicializarAlmacen(int filas, int columnas);
void limpiarMemoriaAlmacen(int filas, int columnas);
void inicializarVectoresP(int tam);
void limpiarMemoriaVectoresP();
void colocarLote(int filas, int columnas, int tam_vectores_p);
void reportePorFila(int filas, int columnas);
void buscarPorComponente(int filas, int columnas, int tam_vectores_p);
void finalizarEjecucion(int filas, int columnas);

// Estructuras y variables globales
typedef struct {
 int idLote;
 char nombreComponente[50];
 float pesoUnitario;
 int cantidadTotal;
} LoteProduccion;

LoteProduccion ***almacen;

LoteProduccion *maestroLotes;
int *indicesDisponibles;

int *pilaIDLote;
int *pilaResultado;

int main() {
    int opc = - 1, filas = 0, columnas = 0, tam_vectores_p = 0;
    bool entrada_valida = false;

    imprimirMensaje("INICIALIZACION", "Inicializando componentes del almacen...");
    // Validar filas y columnas
    while (filas <= 0) {
        std::cout << "Ingrese el numero de filas del almacen: ";
        entrada_valida = validarEntradaNumerica(filas);
        if (entrada_valida) {
            if (filas <= 0) {
                imprimirMensaje("ADVERTENCIA", "El numero de filas debe ser mayor a 0");
            }
        } else {
            imprimirMensaje("ADVERTENCIA", "No se aceptan entradas no numericas para este campo");
        }
    }

    while (columnas <= 0) {
        std::cout << "Ingrese el numero de columnas del almacen: ";
        entrada_valida = validarEntradaNumerica(columnas);
        if (entrada_valida) {
            if (columnas <= 0) {
                imprimirMensaje("ADVERTENCIA", "El numero de columnas debe ser mayor a 0");
            }
        } else {
            imprimirMensaje("ADVERTENCIA", "No se aceptan entradas no numericas para este campo");
        }
    }

    inicializarAlmacen(filas, columnas);
    imprimirMensaje("EXITO", "Almacen inicializado correctamente");

    imprimirMensaje("INICIALIZACION", "Inicializando vectores paralelos...");
    // Validar tamaño de vectores paralelos
    while (tam_vectores_p <= 0) {
        std::cout << "Ingrese el numero de lotes activos : ";
        entrada_valida = validarEntradaNumerica(tam_vectores_p);
        if (entrada_valida) {
            if (tam_vectores_p <= 0) {
                imprimirMensaje("ADVERTENCIA", "El numero de lotes activos debe ser mayor a 0");
            } else if (tam_vectores_p > filas * columnas) {
                imprimirMensaje("ADVERTENCIA", "El numero de lotes activos no puede ser mayor a la capacidad del almacen");
                tam_vectores_p = 0;
            }
        } else {
            imprimirMensaje("ADVERTENCIA", "No se aceptan entradas no numericas para este campo");
        }
    }
    
    inicializarVectoresP(tam_vectores_p);
    imprimirMensaje("EXITO", "Vectores paralelos inicializados correctamente");

    while (opc != 0) {
        opc = imprimirMenu();

        switch (opc) {
        case 1:
            colocarLote(filas, columnas, tam_vectores_p);
            break;
        case 2:
            reportePorFila(filas, columnas);
            break;
        case 3:
            buscarPorComponente(filas, columnas, tam_vectores_p);
            break;
        case 4:
            imprimirMensaje("OPCION", "Control de calidad");
            break; 
        case 5:
            imprimirMensaje("OPCION", "Deshacer inspeccion");
            break;
        case 0:
            finalizarEjecucion(filas, columnas);
            break;
        }
    }

    return 0;
}

int imprimirMenu(){
    int opc_selecc = -1;
    bool entrada_valida = false;

    std::cout << "+---------------------------------------------+" << std::endl;
    std::cout << "|               ALPHATECH                     |" << std::endl;
    std::cout << "+---------------------------------------------+" << std::endl;
    std::cout << "|  1. Colocacion de lote                      |" << std::endl;
    std::cout << "|  2. Reporte por fila                        |" << std::endl;
    std::cout << "|  3. Busqueda por componente                 |" << std::endl;
    std::cout << "|  4. Control de calidad                      |" << std::endl;
    std::cout << "|  5. Deshacer inspeccion                     |" << std::endl;
    std::cout << "|  0. Salir                                   |" << std::endl;
    std::cout << "+---------------------------------------------+" << std::endl;
    // Validar opción del menú
    while (!entrada_valida || opc_selecc < 0 || opc_selecc > 5) {
        std::cout << "Ingrese una opcion (0-5): ";
        entrada_valida = validarEntradaNumerica(opc_selecc);
        
        if (!entrada_valida) {
            imprimirMensaje("ADVERTENCIA", "No se aceptan entradas no numericas para este campo");
        } else if (opc_selecc < 0 || opc_selecc > 5) {
            imprimirMensaje("ADVERTENCIA", "Opcion no valida");
        }
    }
    
    return opc_selecc;
}

void imprimirMensaje(std::string tipo, std::string mensaje){
    std::cout << tipo << ": " << mensaje << std::endl;
}

bool validarEntradaNumerica(int &entrada) {
    std::cin >> entrada;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        return false;
    }
    return true;
}

void inicializarAlmacen(int filas, int columnas) {
    almacen = new LoteProduccion**[filas];
    for (int i = 0; i < filas; i++) {
        almacen[i] = new LoteProduccion*[columnas];
        for (int j = 0; j < columnas; j++) {
            almacen[i][j] = nullptr;  
        }
    }
}

void limpiarMemoriaAlmacen(int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (almacen[i][j] != nullptr) {
                delete almacen[i][j];
                almacen[i][j] = nullptr;
            }
        }
        delete [] almacen[i];
        almacen[i] = nullptr;
    }
    delete [] almacen;
    almacen = nullptr;
}

void inicializarVectoresP(int tam) {
    maestroLotes = new LoteProduccion[tam];
    indicesDisponibles = new int[tam];
    
    for (int i = 0; i < tam; i++) {
        indicesDisponibles[i] = 0;
        maestroLotes[i].idLote = 0;
    }
}

void limpiarMemoriaVectoresP() {
    delete [] maestroLotes;
    maestroLotes = nullptr;

    delete [] indicesDisponibles;
    indicesDisponibles = nullptr;
}

void colocarLote(int filas, int columnas, int tam_vectores_p) {
    int fila, columna;
    bool entrada_valida = false;

    // Validar fila
    while (!entrada_valida || fila < 0 || fila >= filas) {
        std::cout << "Ingrese la fila donde desea colocar el lote (0 a " << filas - 1 << "): ";
        entrada_valida = validarEntradaNumerica(fila);
        if (!entrada_valida || fila < 0 || fila >= filas) {
            imprimirMensaje("ADVERTENCIA", "Fila no valida");
            entrada_valida = false;
        }
    }

    // Validar columna
    entrada_valida = false;
    while (!entrada_valida || columna < 0 || columna >= columnas) {
        std::cout << "Ingrese la columna donde desea colocar el lote (0 a " << columnas - 1 << "): ";
        entrada_valida = validarEntradaNumerica(columna);
        if (!entrada_valida || columna < 0 || columna >= columnas) {
            imprimirMensaje("ADVERTENCIA", "Columna no valida");
            entrada_valida = false;
        }
    }

    // Verificar si la celda está ocupada
    if (almacen[fila][columna] != nullptr) {
        imprimirMensaje("ADVERTENCIA", "La celda ya contiene un lote");
        return;
    }

    // Buscar índice disponible en el maestro de lotes
    int indiceDisponible = -1;
    for (int i = 0; i < tam_vectores_p; i++) {
        if (indicesDisponibles[i] == 0) {
            indiceDisponible = i;
            break;
        }
    }

    if (indiceDisponible == -1) {
        imprimirMensaje("ERROR", "No hay espacio disponible en el maestro de lotes");
        return;
    }

    LoteProduccion* nuevoLote = new LoteProduccion;
    
    // Validar ID único
    bool idUnico = false;
    while (!idUnico) {
        std::cout << "Ingrese el ID del lote: ";
        while (!validarEntradaNumerica(nuevoLote->idLote) || nuevoLote->idLote <= 0) {
            imprimirMensaje("ADVERTENCIA", "ID de lote no valido");
            std::cout << "Ingrese el ID del lote: ";
        }
        
        // Verificar si el ID ya existe
        bool idExiste = false;
        for (int i = 0; i < tam_vectores_p; i++) {
            if (indicesDisponibles[i] == 1 && maestroLotes[i].idLote == nuevoLote->idLote) {
                idExiste = true;
                break;
            }
        }
        
        if (idExiste) {
            imprimirMensaje("ADVERTENCIA", "El ID del lote ya existe. Ingrese un ID diferente.");
        } else {
            idUnico = true;
        }
    }

    std::cin.ignore(1000, '\n');

    // Validar nombre único
    bool nombreUnico = false;
    while (!nombreUnico) {
        std::cout << "Ingrese el nombre del componente: ";
        std::cin.getline(nuevoLote->nombreComponente, 50);
        
        std::string nuevoNombre = nuevoLote->nombreComponente;
        
        // Verificar si el nombre ya existe
        bool nombreExiste = false;
        for (int i = 0; i < tam_vectores_p; i++) {
            if (indicesDisponibles[i] == 1) {
                std::string nombreExistente = maestroLotes[i].nombreComponente;
                if (nombreExistente == nuevoNombre) {
                    nombreExiste = true;
                    break;
                }
            }
        }
        
        if (nombreExiste) {
            imprimirMensaje("ADVERTENCIA", "El nombre del componente ya existe. Ingrese un nombre diferente.");
        } else {
            nombreUnico = true;
        }
    }

    std::cout << "Ingrese el peso unitario: ";
    while (!(std::cin >> nuevoLote->pesoUnitario) || nuevoLote->pesoUnitario <= 0) {
        imprimirMensaje("ADVERTENCIA", "Peso unitario no valido");
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Ingrese el peso unitario: ";
    }

    std::cout << "Ingrese la cantidad total: ";
    while (!validarEntradaNumerica(nuevoLote->cantidadTotal) || nuevoLote->cantidadTotal <= 0) {
        imprimirMensaje("ADVERTENCIA", "Cantidad total no valida");
        std::cout << "Ingrese la cantidad total: ";
    }

    // Asignar el lote al maestro
    maestroLotes[indiceDisponible] = *nuevoLote;
    indicesDisponibles[indiceDisponible] = 1;

    almacen[fila][columna] = nuevoLote;

    imprimirMensaje("EXITO", "Lote colocado correctamente en la posicion (" + 
                   std::to_string(fila) + ", " + std::to_string(columna) + ")");
    
    // Mostrar resumen del lote colocado como confirmación
    std::cout << "Resumen del lote:" << std::endl;
    std::cout << "  ID: " << nuevoLote->idLote << std::endl;
    std::cout << "  Componente: " << nuevoLote->nombreComponente << std::endl;
    std::cout << "  Peso unitario: " << nuevoLote->pesoUnitario << std::endl;
    std::cout << "  Cantidad total: " << nuevoLote->cantidadTotal << std::endl;
}

void reportePorFila(int filas, int columnas) {
    int filaReporte;
    bool entrada_valida = false;
    bool hayLotes = false;

    // Validar fila
    while (!entrada_valida || filaReporte < 0 || filaReporte >= filas) {
        std::cout << "Ingrese el numero de fila a reportar (0 a " << filas - 1 << "): ";
        entrada_valida = validarEntradaNumerica(filaReporte);
        if (!entrada_valida || filaReporte < 0 || filaReporte >= filas) {
            imprimirMensaje("ADVERTENCIA", "Fila no valida");
            entrada_valida = false;
        }
    }

    std::cout << "--- Reporte de Fila " << filaReporte << " ---" << std::endl;
    
    // Recorrer todas las columnas de la fila especificada para verificar cuales estan ocupadas y cuales no
    for (int j = 0; j < columnas; j++) {
        if (almacen[filaReporte][j] != nullptr) {
            std::cout << "(" << filaReporte << ", " << j << "): ";
            std::cout << "ID: " << almacen[filaReporte][j]->idLote << ", ";
            std::cout << "Nombre: " << almacen[filaReporte][j]->nombreComponente << std::endl;
            hayLotes = true;
        } else {
            std::cout << "(" << filaReporte << ", " << j << "): Vacio" << std::endl;
        }
    }
    // Si no se encontraron lotes en la fila, se le avisa al usuario
    if (!hayLotes) {
        imprimirMensaje("INFORMACION", "La fila " + std::to_string(filaReporte) + " no contiene lotes");
    }
}

void buscarPorComponente(int filas, int columnas, int tam_vectores_p) {
    std::string nombreBuscado;
    bool encontrado = false;
    
    std::cout << "Ingrese el nombre del componente a buscar: ";
    std::cin.ignore(1000, '\n');
    std::getline(std::cin, nombreBuscado);
    
    std::cout << "Resultados de la busqueda para: " << nombreBuscado << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (almacen[i][j] != nullptr) { 
                std::string nombreActual = almacen[i][j]->nombreComponente;
                if (nombreActual == nombreBuscado) {
                    std::cout << "Ubicacion: (" << i << ", " << j << ")" << std::endl;
                    std::cout << "  ID del lote: " << almacen[i][j]->idLote << std::endl;
                    std::cout << "  Componente: " << almacen[i][j]->nombreComponente << std::endl;
                    std::cout << "  Peso unitario: " << almacen[i][j]->pesoUnitario << std::endl;
                    std::cout << "  Cantidad total: " << almacen[i][j]->cantidadTotal << std::endl;
                    std::cout << "----------------------------------------" << std::endl;
                    encontrado = true;
                }
            }
        }
    }
    
    if (!encontrado) {
        imprimirMensaje("INFORMACION", "No se encontraron lotes con el componente: " + nombreBuscado);
    }
}

void finalizarEjecucion(int filas, int columnas) {
    limpiarMemoriaAlmacen(filas, columnas);
    imprimirMensaje("LIMPIEZA", "Memoria de almacen liberada...");
    limpiarMemoriaVectoresP();
    imprimirMensaje("LIMPIEZA", "Memoria de vectores paralelos liberada...");
    imprimirMensaje("FIN", "Hasta la proxima...");
}