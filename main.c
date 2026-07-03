#include <stdio.h>
#include "empleados.h"

int main(void) {

    Empleado empleados[MAX_EMPLEADOS];
    int cantidad = 0;
    int opcion;

     if (cargarEmpleados(empleados, &cantidad, ARCHIVO_EMPLEADOS)) {
        printf("Datos cargados desde %s. Registros cargados: %d.\n", ARCHIVO_EMPLEADOS, cantidad);
    } else {
        printf("No se encontro %s. Se iniciara con una lista vacia.\n", ARCHIVO_EMPLEADOS);
    }


do {
        mostrarMenu();
        opcion = leerEntero("Seleccione una opcion: ", 0);

        switch (opcion) {
            case 1:
                registrarEmpleado(empleados, &cantidad);
                break;
            case 2:
                listarEmpleados(empleados, cantidad);
                break;
            case 3:
                buscarEmpleado(empleados, cantidad);
                break;
            case 4:
                actualizarEmpleado(empleados, cantidad);
                break;
            case 5:
                eliminarEmpleado(empleados, &cantidad);
                break;
            case 6:
                if (guardarEmpleados(empleados, cantidad, ARCHIVO_EMPLEADOS)) {
                    printf("Cambios guardados correctamente en %s.\n", ARCHIVO_EMPLEADOS);
                }
                break;
            case 0:
                if (guardarEmpleados(empleados, cantidad, ARCHIVO_EMPLEADOS)) {
                    printf("Cambios guardados automaticamente en %s.\n", ARCHIVO_EMPLEADOS);
                }
                printf("Programa finalizado.\n");
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 0);


      return 0;


}