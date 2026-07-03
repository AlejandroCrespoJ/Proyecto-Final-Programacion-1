#ifndef EMPLEADOS_H
#define EMPLEADOS_H

#define MAX_EMPLEADOS 100
#define MAX_CODIGO 16
#define MAX_NOMBRE 60
#define MAX_CARGO 40
#define ARCHIVO_EMPLEADOS "empleados.csv"
#define VALOR_HORA_EXTRA 5.0f

typedef struct {
    char codigo_empleado[MAX_CODIGO];
    char nombre[MAX_NOMBRE];
    char cargo[MAX_CARGO];
    float sueldo_base;
    int horas_extra;
} Empleado;