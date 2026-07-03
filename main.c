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





}