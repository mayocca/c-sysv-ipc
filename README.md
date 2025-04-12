# Gestión de restaurante

## Descripción

Este proyecto simula la gestión de un restaurante utilizando IPC (Inter-Process Communication) para la comunicación entre procesos.

## Uso

```bash
make

# Ejecutar el productor en una terminal
./producer

# Ejecutar los consumidores en otras terminales
./consumer A
./consumer B
./consumer C
```

## Notas

Por defecto, el productor escribe en el archivo `/tmp/menu.dat` y los consumidores lo leen de ahí.

Para cambiar el archivo, se puede exportar la variable de entorno `FILE_PATH` antes de ejecutar el productor y consumidor.

## Configuración

### Archivo de Menú

El sistema utiliza un archivo para la comunicación entre el productor y los consumidores:

- **Ubicación por defecto**: `/tmp/menu.dat`
- **Variable de entorno**: `FILE_PATH`

### Métodos de Ejecución

#### 1. Usando Variable de Entorno Global

```bash
# Establecer la ruta del archivo
export FILE_PATH=/ruta/al/archivo.dat

# Ejecutar los procesos
./producer                # Inicia el productor
./consumer A             # Consumidor para menú tipo A
./consumer B             # Consumidor para menú tipo B
./consumer C             # Consumidor para menú tipo C
```

#### 2. Variable de Entorno Inline

```bash
# Ejecutar cada proceso con su propia ruta
FILE_PATH=/ruta/al/archivo.dat ./producer
FILE_PATH=/ruta/al/archivo.dat ./consumer A
FILE_PATH=/ruta/al/archivo.dat ./consumer B
FILE_PATH=/ruta/al/archivo.dat ./consumer C
```

### Estructura del Proyecto

```
.
├── include/            # Archivos de cabecera
│   ├── framework/     # Framework de utilidades
│   └── restaurant/    # Lógica del restaurante
├── src/               # Código fuente
│   ├── framework/     # Implementación del framework
│   └── restaurant/    # Implementación del restaurante
├── producer           # Ejecutable del productor
└── consumer          # Ejecutable del consumidor
```

### Compilación

```bash
make clean    # Limpia los archivos compilados
make         # Compila el proyecto
```

## Autor

Este proyecto fue desarrollado por [Matías Yocca](https://github.com/mayocca) para la materia Laboratorio III de la carrera Ingeniería en Informática de la Universidad de Palermo.
