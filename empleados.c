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
int leerEntero(const char *mensaje, int minimo) {
    char linea[80];
    char *fin;
    long valor;

    while (1) {
        leerCadena(mensaje, linea, sizeof(linea));
        valor = strtol(linea, &fin, 10);

        if (*fin == '\0' && valor >= minimo) {
            return (int)valor;
        }

        printf("Entrada invalida. Ingrese un entero mayor o igual a %d.\n", minimo);
    }
}

float leerFloat(const char *mensaje, float minimo) {
    char linea[80];
    char *fin;
    float valor;

    while (1) {
        leerCadena(mensaje, linea, sizeof(linea));
        valor = strtof(linea, &fin);

        if (*fin == '\0' && valor >= minimo) {
            return valor;
        }

        printf("Entrada invalida. Ingrese un numero mayor o igual a %.2f.\n", minimo);
    }
}

nt codigoValido(const char *codigo) {
    int i;
    int longitud = (int)strlen(codigo);

    if (longitud < 1 || longitud > 15) {
        return 0;
    }

    for (i = 0; codigo[i] != '\0'; i++) {
        if (!isalnum((unsigned char)codigo[i])) {
            return 0;
        }
    }

    return 1;
}

int existeCodigo(const Empleado empleados[], int cantidad, const char *codigo) {
    int i;

    for (i = 0; i < cantidad; i++) {
        if (strcmp(empleados[i].codigo_empleado, codigo) == 0) {
            return i;
        }
    }

    return -1;
}

int contieneTexto(const char *texto, const char *busqueda) {
    int i, j;
    int longitudTexto = (int)strlen(texto);
    int longitudBusqueda = (int)strlen(busqueda);

    if (longitudBusqueda == 0) {
        return 1;
    }

    for (i = 0; i <= longitudTexto - longitudBusqueda; i++) {
        for (j = 0; j < longitudBusqueda; j++) {
            if (tolower((unsigned char)texto[i + j]) != tolower((unsigned char)busqueda[j])) {
                break;
            }
        }

        if (j == longitudBusqueda) {
            return 1;
        }
    }

    return 0;
}
float calcularSueldoTotal(const Empleado *empleado) {
    return empleado->sueldo_base + (empleado->horas_extra * VALOR_HORA_EXTRA);
}

void mostrarMenu(void) {
    printf("\nSISTEMA DE GESTION DE EMPLEADOS" "\n");
    printf("1. Registrar empleado\n");
    printf("2. Listar empleados\n");
    printf("3. Buscar empleado\n");
    printf("4. Actualizar empleado\n");
    printf("5. Eliminar empleado\n");
    printf("6. Guardar cambios en archivo\n");
    printf("0. Guardar y salir\n");
    printf("\n");
}

int cargarEmpleados(Empleado empleados[], int *cantidad, const char *nombreArchivo) {
    FILE *archivo;
    char linea[300];
    char *codigo;
    char *nombre;
    char *cargo;
    char *sueldo;
    char *horas;
    Empleado temporal;

    archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL) {
        *cantidad = 0;
        return 0;
    }

    *cantidad = 0;

    fgets(linea, sizeof(linea), archivo);

    while (fgets(linea, sizeof(linea), archivo) != NULL && *cantidad < MAX_EMPLEADOS) {
        limpiarCadena(linea);

        if (strlen(linea) == 0) {
            continue;
        }

        codigo = strtok(linea, ",");
        nombre = strtok(NULL, ",");
        cargo = strtok(NULL, ",");
        sueldo = strtok(NULL, ",");
        horas = strtok(NULL, ",");

        if (codigo == NULL || nombre == NULL || cargo == NULL || sueldo == NULL || horas == NULL) {
            continue;
        }

        limpiarCadena(codigo);
        limpiarCadena(nombre);
        limpiarCadena(cargo);
        limpiarCadena(sueldo);
        limpiarCadena(horas);

        copiarSeguro(temporal.codigo_empleado, codigo, MAX_CODIGO);
        copiarSeguro(temporal.nombre, nombre, MAX_NOMBRE);
        copiarSeguro(temporal.cargo, cargo, MAX_CARGO);
        temporal.sueldo_base = (float)atof(sueldo);
        temporal.horas_extra = atoi(horas);

        if (codigoValido(temporal.codigo_empleado) &&
            temporal.sueldo_base > 0 &&
            temporal.horas_extra >= 0 &&
            existeCodigo(empleados, *cantidad, temporal.codigo_empleado) == -1) {
            empleados[*cantidad] = temporal;
            (*cantidad)++;
        }
    }

    fclose(archivo);
    return 1;
}

int guardarEmpleados(const Empleado empleados[], int cantidad, const char *nombreArchivo) {
    FILE *archivo;
    int i;

    archivo = fopen(nombreArchivo, "w");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para guardar.\n");
        return 0;
    }

    fprintf(archivo, "codigo_empleado,nombre,cargo,sueldo_base,horas_extra\n");

    for (i = 0; i < cantidad; i++) {
        fprintf(archivo, "%s,%s,%s,%.2f,%d\n",
                empleados[i].codigo_empleado,
                empleados[i].nombre,
                empleados[i].cargo,
                empleados[i].sueldo_base,
                empleados[i].horas_extra);
    }

    fclose(archivo);
    return 1;
}

void registrarEmpleado(Empleado empleados[], int *cantidad) {
    Empleado nuevo;

    if (*cantidad >= MAX_EMPLEADOS) {
        printf("No se pueden registrar mas empleados. Capacidad maxima: %d.\n", MAX_EMPLEADOS);
        return;
    }

    printf("\nREGISTRAR EMPLEADO\n");

    while (1) {
        leerCadena("Codigo de empleado: ", nuevo.codigo_empleado, MAX_CODIGO);

        if (!codigoValido(nuevo.codigo_empleado)) {
            printf("Codigo invalido. Use 1 a 15 caracteres alfanumericos, sin espacios.\n");
        } else if (existeCodigo(empleados, *cantidad, nuevo.codigo_empleado) != -1) {
            printf("Ese codigo ya existe. Ingrese un codigo diferente.\n");
        } else {
            break;
        }
    }

    while (1) {
        leerCadena("Nombre: ", nuevo.nombre, MAX_NOMBRE);
        if (tieneComa(nuevo.nombre)) {
            printf("El nombre no puede contener comas porque se guarda en CSV.\n");
        } else {
            break;
        }
    }

    while (1) {
        leerCadena("Cargo: ", nuevo.cargo, MAX_CARGO);
        if (tieneComa(nuevo.cargo)) {
            printf("El cargo no puede contener comas porque se guarda en CSV.\n");
        } else {
            break;
        }
    }

    nuevo.sueldo_base = leerFloat("Sueldo base: ", 0.01f);
    nuevo.horas_extra = leerEntero("Horas extra: ", 0);

    empleados[*cantidad] = nuevo;
    (*cantidad)++;

    printf("Empleado registrado correctamente. Sueldo total: %.2f\n", calcularSueldoTotal(&nuevo));
}
