# Sistema de Gestión Académica "NEXUS"

Este proyecto es un sistema académico interactivo desarrollado en C++ que actúa como interfaz para una base de datos MySQL. Permite gestionar la información de alumnos, visualizar rankings y actualizar datos en tiempo real.


## Características del Sistema

| Módulo | Descripción |
| :--- | :--- |
| **Buscador** | Consulta rápida de alumnos mediante su ID único. |
| **Cuadro de Honor** | Muestra automáticamente el Top 5 de mejores promedios. |
| **Filtros** | Clasificación de alumnos en **Aprobados** (≥ 5) y **Reprobados** (< 5). |
| **Actualización de Datos** | Modificación de notas con recálculo automático del estado y actualización de números de contacto. |

## Requisitos Previos (Entorno Windows)

Para compilar y ejecutar este sistema, tu estación de trabajo debe contar con:
* **Código**: Visual Studio Code, extensión C++.
* **Compilador:** MinGW-w64 (g++) debidamente agregado al PATH del sistema.
* **Gestor de BD:** MySQL Server 8.0 local.
* **Conector:** MySQL Connector/C (API de C para el enlace de datos).


## 1. Configuración de Seguridad

Por razones de seguridad, las credenciales de acceso a la base de datos no se incluyen en este repositorio.

Para ejecutar el proyecto, se debe crear manualmente un archivo llamado `db_config.h` en la carpeta principal del proyecto e ingresar las credenciales locales correspondientes.

```cpp
#ifndef DB_CONFIG_H
#define DB_CONFIG_H

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "tu_password"
#define DB_NAME "sistema"

#endif
```

## 2. Instalación y Puesta en Marcha

### Paso A: Despliegue de Base de Datos
* Abre **MySQL Workbench**.
* Ejecuta el archivo `NEXUS.sql` adjunto en este repo. Esto creará la arquitectura de tablas y los registros iniciales necesarios.

### Paso B: Integración del Driver (DLL)
C++ requiere un driver dinámico para comunicarse con MySQL en Windows:
1. Localiza el archivo `libmysql.dll` en: `C:\Program Files\MySQL\MySQL Server 8.0\lib`.
2. **Cópialo y pégalo** en la carpeta donde está tu `main.cpp`.
   > **Nota:** Sin este archivo, el programa lanzará un error de ejecución inmediatamente.

## 3. Compilación y Ejecución

Abre una terminal en el directorio del proyecto y ejecuta los siguientes comandos de ingeniería:

### Compilación (Vinculación de Librerías)
```powershell
g++ main.cpp -o main.exe -I"C:/Program Files/MySQL/MySQL Server 8.0/include" -L"C:/Program Files/MySQL/MySQL Server 8.0/lib" -lmysql
```

### Ejecución
```powershell
.\main.exe
```

---

## Estructura del Repositorio
```bash
├── main.cpp        # Lógica de control y queries SQL
├── NEXUS.sql       # Script de creación de la base de datos
├── .gitignore      # Exclusión de binarios y datos sensibles
├── libmysql.dll    # Driver de conexión para Windows
└── README.md       # Documentación técnica (este archivo)
```

---

