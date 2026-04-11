# Alpha Engine

**Open Source Modular Game Engine**  
*Built with C++ for maximum performance and flexibility*

<p align="center">
  <img src="https://i.ibb.co/LprNYRR/Alpha-Engine-2.png" alt="Alpha Engine Logo" width="280">
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Version-v0.1_Alpha-blue" alt="Version">
  <img src="https://img.shields.io/badge/License-MIT-green" alt="License">
  <img src="https://img.shields.io/github/last-commit/Quark-Hell/Alpha_Engine" alt="Last Commit">
  <img src="https://img.shields.io/github/languages/code-size/Quark-Hell/Alpha_Engine" alt="Code Size">
</p>

## About

**Alpha Engine** is a lightweight, modular, and highly extensible game engine focused on performance and clean architecture.

Instead of providing a rigid set of features, the engine offers a powerful foundation of systems and architecture. All gameplay, rendering, physics, audio, and other functionality is implemented through modular systems — giving developers complete freedom to build exactly what they need.

This makes Alpha Engine not just a game engine, but a **meta-framework** suitable for games, tools, simulations, and other high-performance applications.

> ⚠️ The engine is currently in **early alpha** stage and is under active development.

## Features

- Fully modular architecture
- High performance C++20 codebase
- Clean separation of systems
- Easy to extend and customize
- Statically linked external dependencies
- Cross-platform support (Windows & Linux)

## Screenshots

<p align="center">
  <img src="https://i.ibb.co/HDTpqGXh/Game.png" alt="Game Screenshot" width="49%" style="margin: 4px; border-radius: 8px;">
  <img src="https://i.ibb.co/S4gGtXKJ/Logs.png" alt="Engine Logs" width="49%" style="margin: 4px; border-radius: 8px;">
</p>

## Architecture

<p align="center">
  <img src="https://i.ibb.co/mCCnCRps/Architect.png" alt="Alpha Engine Architecture" width="75%" style="margin: 10px; border-radius: 8px;">
</p>

## Documentation

Full documentation is available in a separate repository:

→ **[Alpha Engine Documentation](https://github.com/Quark-Hell/Alpha_Engine_Docs)**

Also check out the [Examples folder](https://github.com/Quark-Hell/Alpha_Engine/tree/Architect2.0/ALPHA_Engine/Examples).

## Build

### Windows (Visual Studio / CLion)

1. Clone the repository
2. Open the project in Visual Studio
3. Build in **Debug** or **Release** configuration

### Linux

```bash
git clone https://github.com/Quark-Hell/Alpha_Engine.git
cd Alpha_Engine/ALPHA_Engine

mkdir build && cd build

cmake -G "Ninja" \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_C_COMPILER=clang \
      -DCMAKE_CXX_COMPILER=clang++ ..

ninja
