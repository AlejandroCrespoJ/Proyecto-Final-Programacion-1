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
