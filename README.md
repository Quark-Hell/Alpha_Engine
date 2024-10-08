# Alpha Engine
Game Engine For Simulators

<p align="center">
      <img src="https://i.ibb.co/LprNYRR/Alpha-Engine-2.png" alt="Alpha-Engine-2" border="0">
</p>

<p align="center">
   <img src="https://img.shields.io/badge/Version-v0.1--Alpha-blue" alt="Engine Version">
   <img src="https://img.shields.io/badge/License-MIT-green" alt="License">
   <img src="https://img.shields.io/github/last-commit/Quark-Hell/Alpha_Engine" alt="Last Update">
   <img src="https://img.shields.io/github/languages/code-size/Quark-Hell/Alpha_Engine" alt="Size">
</p>

## About

This game engine is being developed to make it easier for developers to create simulators. The game engine is absolutely free for use.

## Documentation

- In developing

## Developers

- [Quark](https://github.com/Quark-Hell)

## License
- MIT License

## Build
### Windows with MSVC:

<b>Step 1:</b>
In CMake GUI select engine folder and target folder, after that click configure and generate it.
<br><b>Step 2:</br></b>
In Visual Studio rebuild projects as you need(Debug or Release)
<br><b>Step 3:</br></b>
Move .lib file from Debug or Release folder in ALPHA_Engine/lib folder (should actually happen automatically, so this will be fixed in next release)
<br><b>Step 4:</br></b>
Move ALPHA_Engine and Source into another folder and use project as CMake project. CMakeList.txt generate in Source folder automatically
<br><b>Step 5:</br></b>
Move CMakeList.txt from source to root directory of your project.
You should get the following structure:
<p align="center">
      <img src="https://i.ibb.co/TWH4Rn2/image-2024-10-08-074747846.png" alt="image-2024-10-08-074747846" border="0">
      <img src="https://i.ibb.co/b54Fhsg/image-2024-10-08-075251718.png" alt="image-2024-10-08-075251718" border="0">
</p>
<br><b>Step 6(This step will be removed into next update):</br></b>
Add next lines into Game CMakeList:

```
SET(CMAKE_CXX_FLAGS "-Wall -frtti")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")
```
<br><b>Step 6:</br></b>
Run game project as CMake project
