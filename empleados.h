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

void mostrarMenu(void);

int cargarEmpleados(Empleado empleados[], int *cantidad, const char *nombreArchivo);
int guardarEmpleados(const Empleado empleados[], int cantidad, const char *nombreArchivo);

void registrarEmpleado(Empleado empleados[], int *cantidad);
void listarEmpleados(const Empleado empleados[], int cantidad);
void buscarEmpleado(const Empleado empleados[], int cantidad);
void actualizarEmpleado(Empleado empleados[], int cantidad);
void eliminarEmpleado(Empleado empleados[], int *cantidad);

float calcularSueldoTotal(const Empleado *empleado);

int leerEntero(const char *mensaje, int minimo);
float leerFloat(const char *mensaje, float minimo);
void leerCadena(const char *mensaje, char destino[], int tamano);
void limpiarCadena(char cadena[]);

int codigoValido(const char *codigo);
int existeCodigo(const Empleado empleados[], int cantidad, const char *codigo);
int contieneTexto(const char *texto, const char *busqueda);