# axl.game

A simple multiplatform C++ and OpenGL based game library.

## Versions and supported platforms

- Latest version: 0.10.35 alpha
- Currently supported platforms: **Windows**

## Library Headers

- [axl.game/lib.hpp](/include/axl.game/lib.hpp) - The library header. Contains **library version**, **library type** and **build type**.
- [axl.game/platform.h](/include/axl.game/platform.h) - Defines the PLATFORM and ABI based on the building platform.
- [axl.game/Application.hpp](/include/axl.game/Application.hpp) - Application class containing static methods to control the app.
- [axl.game/View.hpp](/include/axl.game/View.hpp) - Main View class, Window or Activity depending in the platform, provided as a generalized class.
- [axl.game/Context.hpp](/include/axl.game/Context.hpp) - The OpenGL context class.
- [axl.game/input/KeyCodes.hpp](/include/axl.game/KeyCodes.hpp) - Key codes.
- [axl.game/input/Keyboard.hpp](/include/axl.game/Keyboard.hpp) - Keyboard input functions and key input listener.
- [axl.game/input/Mouse.hpp](/include/axl.game/Mouse.hpp) - Mouse input functions and mouse input listener.
- [axl.game/input/Touch.hpp](/include/axl.game/Touch.hpp) - Touch input functions.

## Requirements

- Windows operating system. (Linux and other platforms implementations are on the way)
- CMake 3.10 or above.
- Any C and C++ SDK that can be accessed through a command line. (MSVC, MinGW) If you have Visual Studio or CodeBlocks then you are set.

## Dependencies

- [axl.glw](https://github.com/defalt8/axl.glw.git)
- [axl.math](https://github.com/defalt8/axl.math.git)
- [axl.util](https://github.com/defalt8/axl.util.git)

## How to get started

- Clone these repos into a directory and execute these commands to build the library.
  - git clone https://github.com/defalt8/axl.game.git
  - git clone https://github.com/defalt8/axl.glw.git
  - git clone https://github.com/defalt8/axl.math.git
  - git clone https://github.com/defalt8/axl.util.git
  - cd axl.game
  - mkdir out\\build
  - cd out\\build
  - cmake -B . -S ../../ (or with a generator of your choosing.) cmake -G \<generator\> -B . -S ../../
  - cmake --build .

## CMake Options

Default values are marked **bold**.

- General options
  - BUILD_TESTS=[ON|**OFF**]
  - BUILD_TOOLS=[ON|**OFF**]
  - INSTALL_HEADERS=[**ON**|OFF]
  - INSTALL_ARCHIVES=[**ON**|OFF]
  - INSTALL_BINARIES=[**ON**|OFF]

- Library specific options
  - ***axl.game***
    - LIBAXLGAME_TYPE=[**STATIC**|SHARED]
    - LIBAXLGAME_BUILD_TESTS=[**ON**|OFF]
    - LIBAXLGAME_INSTALL_HEADERS=[**ON**|OFF]
    - LIBAXLGAME_INSTALL_ARCHIVES=[**ON**|OFF]
    - LIBAXLGAME_INSTALL_BINARIES=[**ON**|OFF]
  - ***axl.glw***
    - LIBAXLGLW_TYPE=[**STATIC**|SHARED]
    - LIBAXLGLW_BUILD_TESTS=[ON|**OFF**]
    - LIBAXLGLW_BUILD_TOOLS=[ON|**OFF**]
    - LIBAXLGLW_INSTALL_HEADERS=[ON|**OFF**]
    - LIBAXLGLW_INSTALL_ARCHIVES=[ON|**OFF**]
    - LIBAXLGLW_INSTALL_BINARIES=[ON|**OFF**]
  - ***axl.math***
    - LIBAXLMATH_TYPE=[**STATIC**|SHARED]
    - LIBAXLMATH_BUILD_TESTS=[ON|**OFF**]
    - LIBAXLMATH_INSTALL_HEADERS=[ON|**OFF**]
    - LIBAXLMATH_INSTALL_ARCHIVES=[ON|**OFF**]
    - LIBAXLMATH_INSTALL_BINARIES=[ON|**OFF**]
  - ***axl.util***
    - LIBAXLUTIL_TYPE=[**STATIC**|SHARED]
    - LIBAXLUTIL_BUILD_TESTS=[ON|**OFF**]
    - LIBAXLUTIL_INSTALL_HEADERS=[ON|**OFF**]
    - LIBAXLUTIL_INSTALL_ARCHIVES=[ON|**OFF**]
    - LIBAXLUTIL_INSTALL_BINARIES=[ON|**OFF**]
