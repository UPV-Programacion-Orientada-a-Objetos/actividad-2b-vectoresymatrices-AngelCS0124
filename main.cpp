#include <iostream>

// Prototipos de funciones
int imprimirMenu();
void imprimirMensaje(std::string tipo, std::string mensaje);
bool validarEntradaNumerica(int &entrada);
void inicializarAlmacen(int filas, int columnas);
void limpiarMemoriaAlmacen(int filas);
void inicializarVectoresP(int tam);
void limpiarMemoriaVectoresP();
void colocarLote(int filas, int columnas, int tam_vectores_p);
void finalizarEjecucion(int filas);

// Estructuras y variables globales
typedef struct {
 int idLote;
 char nombreComponente[50];
 float pesoUnitario;
 int cantidadTotal;
} LoteProduccion;

LoteProduccion **almacen;

LoteProduccion *maestroLotes;
int *indicesDisponibles;

int *pilaIDLote;
int *pilaResultado;

int main() {
    int opc = - 1, filas = 0, columnas = 0, tam_vectores_p = 0;
    bool entrada_valida = false;

    imprimirMensaje("INICIALIZACION", "Inicializando componentes del almacen...");
    
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
            imprimirMensaje("OPCION", "Reporte por fila");
            break;
        case 3:
            imprimirMensaje("OPCION", "Busqueda por componente");
            break;
        case 4:
            imprimirMensaje("OPCION", "Control de calidad");
            break; 
        case 5:
            imprimirMensaje("OPCION", "Deshacer inspeccion");
            break;
        case 0:
            finalizarEjecucion(filas);
            break;
        default:
            imprimirMensaje("ERROR", "Opcion no reconocida");
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
    almacen = new LoteProduccion *[filas];
    for (int i = 0; i < filas; i++) {
        almacen[i] = new LoteProduccion[columnas];
    }
}

void limpiarMemoriaAlmacen(int filas) {
    for (int i = 0; i < filas; i++) {
        delete [] almacen[i];
        almacen[i] = nullptr;
    }
    delete [] almacen;
    almacen = nullptr;
}

void inicializarVectoresP(int tam) {
    maestroLotes = new LoteProduccion[tam];
    indicesDisponibles = new int[tam];
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

    while (!entrada_valida || fila < 0 || fila >= filas) {
        std::cout << "Ingrese la fila donde desea colocar el lote (0 a " << filas - 1 << "): ";
        entrada_valida = validarEntradaNumerica(fila);
        if (!entrada_valida || fila < 0 || fila >= filas) {
            imprimirMensaje("ADVERTENCIA", "Fila no valida");
            entrada_valida = false;
        }
    }

    while (!entrada_valida || columna < 0 || columna >= columnas) {
        std::cout << "Ingrese la columna donde desea colocar el lote (0 a " << columnas - 1 << "): ";
        entrada_valida = validarEntradaNumerica(columna);
        if (!entrada_valida || columna < 0 || columna >= columnas) {
            imprimirMensaje("ADVERTENCIA", "Columna no valida");
            entrada_valida = false;
        }
    }
}

void finalizarEjecucion(int filas) {
    limpiarMemoriaAlmacen(filas);
    imprimirMensaje("LIMPIEZA", "Memoria de almacen liberada...");
    limpiarMemoriaVectoresP();
    imprimirMensaje("LIMPIEZA", "Memoria de vectores paralelos liberada...");
    imprimirMensaje("FIN", "Hasta la proxima...");
}