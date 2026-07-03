Sistema de Gestion de Empleados - Caso 3

Proyecto para ISWZ1102 - Programacion I.

Integrantes:
- Alejandro Crespo
- Andres Cabrera

Descripcion

Programa en C para gestionar empleados y calcular sueldo mensual con horas extra.
La informacion se carga y guarda en un archivo CSV llamado `empleados.csv`.

Requisitos cubiertos

- Arreglos: arreglo `Empleado empleados[MAX_EMPLEADOS]`.
- Estructuras: `typedef struct Empleado`.
- Funciones: registro, listado, busqueda, actualizacion, eliminacion, carga y guardado.
- Punteros: uso de `int *cantidad`, `Empleado *empleado` y paso por referencia.
- Archivos planos: lectura y escritura de `empleados.csv`.
- Modularidad: separacion en `.h` y `.c`.

Compilacion

```bash
gcc -Wall -Wextra -std=c11 main.c empleados.c utilidades.c -o gestion_empleados
```

Tambien se puede usar:

```bash
make
./gestion_empleados
```

Formato del archivo CSV

```csv
codigo_empleado,nombre,cargo,sueldo_base,horas_extra
E001,Pedro Lopez,Tecnico,500.00,10
```

Menu del sistema

1. Registrar empleado
2. Listar empleados
3. Buscar empleado
4. Actualizar empleado
5. Eliminar empleado
6. Guardar cambios en archivo
7. Salir

