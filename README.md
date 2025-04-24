# Gestión de alquileres - AlquiCor

## Descripción

Este proyecto simula la gestión de alquileres de propiedades utilizando IPC (Inter-Process Communication) para la comunicación entre procesos.

El manager se encarga de gestionar las propiedades y los requests de los clientes, y los clientes se encargan de solicitar alquileres de las propiedades.

## Uso

```bash
make

# Ejecutar el manager en una terminal
./manager

# Ejecutar el client en otra terminal
./client
```

## Notas

Por defecto, los procesos usan los archivos `/tmp/alquicor-properties.dat` y `/tmp/alquicor-requests.dat` para la comunicación entre el manager y el client.

Para cambiar los archivos, se puede exportar la variable de entorno `ALQUICOR_PROPERTIES_PATH` y `ALQUICOR_REQUESTS_PATH` antes de ejecutar el manager y el client.

### Métodos de Ejecución

#### 1. Usando Variable de Entorno Global

```bash
# Establecer la ruta del archivo
export ALQUICOR_PROPERTIES_PATH=/ruta/al/archivo.dat

# Ejecutar los procesos
./manager                # Inicia el manager
./client                 # Inicia el client
```

#### 2. Variable de Entorno Inline

```bash
# Ejecutar cada proceso con su propia ruta
ALQUICOR_PROPERTIES_PATH=/ruta/al/archivo/properties.dat ALQUICOR_REQUESTS_PATH=/ruta/al/archivo/requests.dat ./manager
ALQUICOR_PROPERTIES_PATH=/ruta/al/archivo/properties.dat ALQUICOR_REQUESTS_PATH=/ruta/al/archivo/requests.dat ./client
```

### Estructura del Proyecto

```
.
├── include/            # Archivos de cabecera
│   ├── framework/     # Framework de utilidades
│   └── alquicor/       # Lógica del alquicor
├── src/               # Código fuente
│   ├── framework/     # Implementación del framework
│   └── alquicor/       # Implementación del alquicor
├── manager            # Ejecutable del manager
└── client             # Ejecutable del client
```

### Compilación

```bash
make          # Compila el proyecto
make clean    # Limpia los archivos compilados
```

## Autor

Este proyecto fue desarrollado por [Matías Yocca](https://github.com/mayocca) para el parcial I de la materia Laboratorio III de la carrera Ingeniería en Informática de la Universidad de Palermo.
