# Alpha Engine
Open source game engine

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

- In developing, but you can check [examples](https://github.com/Quark-Hell/Alpha_Engine/tree/Architect2.0/ALPHA_Engine/Examples)

## Developers
- [Quark](https://github.com/Quark-Hell)
- [Kleshovdd](https://github.com/kleshovdd)

## License
- MIT License

## Build
### Windows with Visual Studio or CLion(MinGW compiler):
<pre>
<b>Step 1:</b> Clone repository to your computer and switch to the "Architect2.0" branch
<b>Step 2:</b> In Visual Studio build project as you need(Debug or Release)
<b>Step 3:</b> Enjoy
</pre>

### Linux(tested with: manjaro, arch and openSUSE):

<b>Step 1:</b>
Clone the repo
```
git clone https://github.com/Quark-Hell/Alpha_Engine.git --branch Architect2.0   
```
<b>Step 2:</b>
Go to the Engine source directory and create build folder. Then generate cmake files(I use ninja as generator and clang as compiler, but make will work too):
```
cd Alpha_Engine/ALPHA_Engine  
mkdir build
cmake -G "Ninja" -D CMAKE_BUILD_TYPE=Release -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -B build
```
<b>Step 3:</b>
Build engine
```
cd build
ninja
```
Done

## Note
<pre>
Folder "Build" contains files needed for linking with your project
External dependencies do not included. Check this <a href="https://github.com/Quark-Hell/Alpha_Engine_Dependencies">repo</a> for download it
Or check folder "build/Examples/external" if you build with it        
</pre>
