# Minesweeper

![Example1](./screenshots/gameExample1.png)

## A simple, native, cross-platform Minesweeper game made with C++ and wxWidgets

This program is a basic Minesweeper game that lets you customize the grid size and the number of mines.

![ExampleInit](./screenshots/initExample.png)

The game features a graphical user interface built with wxWidgets.

![Example2](./screenshots/gameExample2.png)

The game ensures that the first clicked square is never a mine, and allows you to reveal surrounding tiles when the number of placed flags matches the number shown on the tile.

![Example3](./screenshots/gameExample3.png)

An in-game timer tracks and displays how long it takes you to complete the game.

![ExampleEnd](./screenshots/endExample.png)

All image assets are original pixel graphics, hand-made specifically for this game.

## Gameplay

The game ends when you either uncover all safe squares or trigger a mine.

**Left mouse button:** Reveal tiles

**Right mouse button:** Place or remove flags


## Development
This project was developed as a programming assignment by Veeti Velin and Miikka Tervo.

The application was written in C++ using the standard library and [wxWidgets GUI library](https://wxwidgets.org/). The application was built using the [CMake build system](https://cmake.org/) with 
a modified version of the [wxWidgets CMake template](https://github.com/lszl84/wx_cmake_fetchcontent_template) created by [lszl84](https://github.com/lszl84). These tools are used under their respective open-source licenses; a copy of the MIT license for the wxWidgets CMake template is included in the ./ThirdPartyLicenses/ folder.

## Terminal Version

The project also includes a simplified version of the game that runs in the terminal and is built using a Makefile.

![ExampleT1](./screenshots/terminalExample1.png)

![ExampleT2](./screenshots/terminalExample2.png)
