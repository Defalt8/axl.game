# axl.game

A simple multiplatform C++ and OpenGL based game library.

## Versions and supported platforms

- Latest version: 0.7.28 alpha
- Currently supported platforms: **Windows**

## Library Headers

- [axl.game/lib.hpp](/include/axl.game/lib.hpp) - The library header. Contains **library version**, **library type** and **build type**.
- [axl.game/Application.hpp](/include/axl.game/Application.hpp) - Application class containing static methods to control the app.
- [axl.game/KeyCodes.hpp](/include/axl.game/KeyCodes.hpp) - General KeyCodes enumerations.
- [axl.game/KeyMap.hpp](/include/axl.game/KeyMap.hpp) - Contains functions to map key codes from library to platform specific and vise versa.
- [axl.game/View.hpp](/include/axl.game/View.hpp) - Main View class, Window or Activity depending in the platform, provided as a generalized class.
- [axl.game/Context.hpp](/include/axl.game/Context.hpp) - The OpenGL context class.
