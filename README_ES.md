~~~
+========================================================================+
|███████╗ ██████╗    ██╗     ██╗██████╗ ██████╗  █████╗ ██████╗ ██╗   ██╗|
|██╔════╝██╔════╝    ██║     ██║██╔══██╗██╔══██╗██╔══██╗██╔══██╗╚██╗ ██╔╝|
|███████╗██║         ██║     ██║██████╔╝██████╔╝███████║██████╔╝ ╚████╔╝ |
|╚════██║██║         ██║     ██║██╔══██╗██╔══██╗██╔══██║██╔══██╗  ╚██╔╝  |
|███████║╚██████╗    ███████╗██║██████╔╝██║  ██║██║  ██║██║  ██║   ██║   |
|╚══════╝ ╚═════╝    ╚══════╝╚═╝╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   |
+========================================================================+    
~~~
Este complemento es una biblioteca que contiene +40 funciones y 5 clases de C++ que van desde poder cambiar entre diferentes pantallas/monitores, establecer la ventana siempre por encima, cambiar la posición de la ventana, uso de (cpu, ram, vram, etc) y mucho más.

------------
# Instalación
>- Descargue el repositorio.
>- Coloque la carpeta `SC_Library` en el directorio `Plugins` de su proyecto de Unreal Engine.
>- Compilar el complemento.

> [!IMPORTANT]
> [DOCUMENTACIÓN](https://buttered-poet-a44.notion.site/SC_Library-Documentation-1ac82a55a8d680919701cac82f9cbc2c?pvs=4)

## Compatibilidad

Versiones de Unreal Engine compatibles : UE5.0 o posterior

Plataformas de destino : Windows

# Construyendo el plugin

> [!CAUTION]
> Si usted NO construyó su proyecto con C++, a la hora de empaquetarlo este no funcionará, por eso es fundamental tener C++ en su proyecto.
Si usted ya tiene C++ en su proyecto, solo debe construir su proyecto y el empaquetado funcionará correctamente, pero si no lo tiene, lo invito a ver este tutorial. [C++ Tutorial](https://youtu.be/EhD5Kff79Jo)

## Build

1. En la carpeta de su proyecto, cree una carpeta de complementos `C:/UnrealProjects/MyProject/Plugins`

1. Clonar el repositorio en la carpeta del complemento

1. Abra su proyecto en su IDE y compile el proyecto.

1. Si todo se ha compilado correctamente, puedes conservar el complemento local en tu proyecto o moverlo a la carpeta de complementos del motor. 
    * `%PROJECT_DIR%/Plugins`

    ------------
# Historial
- [x] [00/00/2025] Lanzamiento