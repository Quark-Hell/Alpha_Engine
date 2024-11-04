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
### Windows with Visual Studio:

<br><b>Step 1:</br></b>
Clone repository to your computer and switch to the "Architect2.0" branch
<br><b>Step 2:</br></b>
In Visual Studio build project as you need(Debug or Release)
<br><b>Step 3:</br></b>
Open .../"repositoryPath"/Sandbox/"yourBuildType"/Game in visual studio and biuld project as you need(Debug or Release)
<br><b>Step 4:</br></b>
Enjoy

<br></br>
### Linux(tested with: manjaro, arch and openSUSE):

<b>Step 1:</b>
Clone the repo
```
git clone https://github.com/Quark-Hell/Alpha_Engine.git
```
<b>Step 2:</b>
Go to the repo folder and switch branch:
```
cd Alpha_Engine
git checkout Architect2.0   
```
<b>Step 3:</b>
Go to the Engine source directory and create build folder.Then generate cmake files(I use ninja as generator and clang as compiler, but make will work too):
```
cd ALPHA_Engine
mkdir build
cmake -G "Ninja" -D CMAKE_BUILD_TYPE=Release -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -B build
```
<b>Step 4:</b>
Build engine
```
cd build
ninja
```
Now engine automatically generate sandbox by path .../Alpha_Engine/Sandbox/"BuildType"/Game. Go to this folder.

<b>Step 5:</b>
Create folder for game and build it:
```
mkdir game_build 
cmake -G "Ninja" -D CMAKE_BUILD_TYPE=Release -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -B game_build
cd game_build
ninja
```
<b>Step 6:</b>
Go to the game build folder and run sandbox project
```
cd game_build
./Game
```

Done
