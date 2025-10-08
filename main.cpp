#include <iostream>

int imprimirMenu();
void imprimirMensaje(std::string tipo, std::string mensaje);

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
    int opc = - 1;

    while (opc != 0) {
        opc = imprimirMenu();

        switch (opc) {
        case 1:
            imprimirMensaje("OPTION", "Colocacion de lote");
            break;
        case 2:
            imprimirMensaje("OPTION", "Reporte por fila");
            break;
        case 3:
            imprimirMensaje("OPTION", "Busqueda por componente");
            break;
        case 4:
            imprimirMensaje("OPTION", "Control de calidad");
            break; 
        case 5:
            imprimirMensaje("OPTION", "Deshacer inspeccion");
            break;
        case 0:
            imprimirMensaje("LOG OUT:", "Hasta la proxima...");
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
            imprimirMensaje("WARNING", "Opcion no valida");
        }
    }
    
    return opc_selecc;
}

void imprimirMensaje(std::string tipo, std::string mensaje){
    std::cout << tipo << ": " << mensaje << std::endl;
}