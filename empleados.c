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
