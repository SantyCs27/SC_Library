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
This plugin is a library that contains +40 functions and 5 C++ classes that range from being able to switch between different screens/monitors, set the window always on top, change the position of the window, use of (cpu, ram, vram, etc) and much more.

------------
# Installation
>- Download this repository.
>- Place the `SC_Library` folder in your Unreal Engine project's `Plugins` directory.
>- Compile the plugin.

> [!IMPORTANT]
> [DOCUMENTATION](https://buttered-poet-a44.notion.site/SC_Library-Documentation-1ac82a55a8d680919701cac82f9cbc2c?pvs=4)

## Compatibility

Supported Unreal Engine Versions : UE5.0 or later

Supported Target Platforms : Windows

# Building the plugin

There are two methods of building the plugin. I suggest using the first method if you have a C++ project setup.
> [!CAUTION]
> If you did NOT build your project with C++, when it comes to packaging it will not work, so it is essential to have C++ in your project.
If you already have C++ in your project, you just need to build your project and the packaging will work correctly, but if you don't, I invite you to watch this tutorial. [C++ Tutorial](https://youtu.be/EhD5Kff79Jo)

## Normal

1. In your project folder, create a plugin folder `C:/UnrealProjects/MyProject/Plugins`

1. Clone the repo into the plugin folder

1. Open your project in your IDE and build the project

1. If everything built successfully, you can keep the plugin local to your project. Or you can move it into the engine plugin folder. 
    * `%PROJECT_DIR%/Plugins`

## Using RunUAT.bat

1. Clone the repo
1. Open the command prompt and run the UnrealEngine batch file to build the plugin, with your download location and out location.

> "`%UNREAL_DESIRED%`/Engine/Build/BatchFiles/RunUAT.bat" BuildPlugin -Plugin="`%DOWNLOAD_LOCATION%`/SC_Library/SC_Library.uplugin" -Package="`%OUT_LOCATION%`" -CreateSubFolder

Example: Building for desired version `UE_5.0`:

* `%UNREAL_DESIRED%`: C:/Program Files/Epic Games/UE_5.0
* `%DOWNLOAD_LOCATION%`: C:/Downloads
* `%OUT_LOCATION%`: C:Downloads/SC_Library

> "**C:/Program Files/Epic Games/UE_5.0/Engine/Build/BatchFiles/RunUAT.bat**" BuildPlugin -Plugin="**C:Temp/SC_Library/SC_Library.uplugin**" -Package="**C:/TempSC_Library**" -CreateSubFolder

4. Copy the built plugin folder from your package location (`C:/TempSC_Library/SC_Library`) into either your:
    * Project plugin location `%PROJECT_DIR%/Plugins`

    ------------
# History
- [x] [00/00/2025] Launch