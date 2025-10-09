#include <iostream>

int imprimirMenu();
void imprimirMensaje(std::string tipo, std::string mensaje);
void inicializarAlmacen(int filas, int columnas);
void inicializarVectoresP(int tam);
bool validarEntradaNumerica(int &entrada);

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

    imprimirMensaje("INICIO", "Favor de inicializar los componentes del almacen");
    
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

    imprimirMensaje("EXITO", "Componentes del almacen inicializados correctamente");

    while (opc != 0) {
        opc = imprimirMenu();

        switch (opc) {
        case 1:
            imprimirMensaje("OPCION", "Colocacion de lote");
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
            imprimirMensaje("FIN", "Hasta la proxima...");
            break;
        }
    }

    return 0;
}

int imprimirMenu(){
    int opc_selecc = -1;

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

    while (opc_selecc < 0 || opc_selecc > 5) {
        std::cout << "Ingrese una opcion (0-5): ";
        std::cin >> opc_selecc;

        if (opc_selecc < 0 || opc_selecc > 5) {
            imprimirMensaje("ADVERTENCIA", "Opcion no valida");
        }
    }
    
    return opc_selecc;
}

void imprimirMensaje(std::string tipo, std::string mensaje){
    std::cout << tipo << ": " << mensaje << std::endl;
}

void inicializarAlmacen(int filas, int columnas) {
    almacen = new LoteProduccion *[filas];
    for (int i = 0; i < filas; i++) {
        almacen[i] = new LoteProduccion[columnas];
    }
}

void inicializarVectoresP(int tam) {
    maestroLotes = new LoteProduccion[tam];
    indicesDisponibles = new int[tam];
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
