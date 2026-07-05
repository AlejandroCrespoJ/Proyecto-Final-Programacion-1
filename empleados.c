#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "empleados.h"

static void limpiarBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static int tieneComa(const char *cadena) {
    return strchr(cadena, ',') != NULL;
}

static void copiarSeguro(char destino[], const char *origen, int tamano) {
    strncpy(destino, origen, tamano - 1);
    destino[tamano - 1] = '\0';
}

static void leerCadenaOpcional(const char *mensaje, char destino[], int tamano) {
    int textoLargo;

    do {
        printf("%s", mensaje);

        if (fgets(destino, tamano, stdin) == NULL) {
            destino[0] = '\0';
            return;
        }

        textoLargo = strchr(destino, '\n') == NULL;
        if (textoLargo) {
            limpiarBufferEntrada();
            printf("Entrada demasiado larga. Intente nuevamente.\n");
            destino[0] = '\0';
        } else {
            limpiarCadena(destino);
        }
    } while (textoLargo);
}

static int leerFloatOpcional(const char *mensaje, float minimo, float *valor) {
    char linea[80];
    char *fin;
    float temporal;

    while (1) {
        leerCadenaOpcional(mensaje, linea, sizeof(linea));

        if (strlen(linea) == 0) {
            return 0;
        }

        temporal = strtof(linea, &fin);

        if (*fin == '\0' && temporal >= minimo) {
            *valor = temporal;
            return 1;
        }

        printf("Valor invalido. Debe ser un numero mayor o igual a %.2f.\n", minimo);
    }
}

static int leerEnteroOpcional(const char *mensaje, int minimo, int *valor) {
    char linea[80];
    char *fin;
    long temporal;

    while (1) {
        leerCadenaOpcional(mensaje, linea, sizeof(linea));

        if (strlen(linea) == 0) {
            return 0;
        }

        temporal = strtol(linea, &fin, 10);

        if (*fin == '\0' && temporal >= minimo) {
            *valor = (int)temporal;
            return 1;
        }

        printf("Valor invalido. Debe ser un numero entero mayor o igual a %d.\n", minimo);
    }
}static void imprimirCabeceraTabla(void) {
    printf("%-15s %-25s %-20s %12s %12s %12s\n",
           "CODIGO", "NOMBRE", "CARGO", "BASE", "H. EXTRA", "TOTAL");
    printf("\n");
}

static void imprimirEmpleadoTabla(const Empleado *empleado) {
    printf("%-15s %-25s %-20s %12.2f %12d %12.2f\n",
           empleado->codigo_empleado,
           empleado->nombre,
           empleado->cargo,
           empleado->sueldo_base,
           empleado->horas_extra,
           calcularSueldoTotal(empleado));
}

void limpiarCadena(char cadena[]) {
    int inicio = 0;
    int i;
    size_t longitud;

    longitud = strlen(cadena);

    while (longitud > 0 && isspace((unsigned char)cadena[longitud - 1])) {
        cadena[longitud - 1] = '\0';
        longitud--;
    }

    while (cadena[inicio] != '\0' && isspace((unsigned char)cadena[inicio])) {
        inicio++;
    }

    if (inicio > 0) {
        for (i = 0; cadena[inicio + i] != '\0'; i++) {
            cadena[i] = cadena[inicio + i];
        }
        cadena[i] = '\0';
    }
}

void leerCadena(const char *mensaje, char destino[], int tamano) {
    do {
        leerCadenaOpcional(mensaje, destino, tamano);

        if (strlen(destino) == 0) {
            printf("Este campo no puede estar vacio.\n");
        }
    } while (strlen(destino) == 0);
}
