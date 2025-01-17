# Cloning

Remember to also clone submodules for Raylib.

```
git clone --recurse-submodules https://github.com/AlejandroSuau/rts_game.git
```

# Building

## MacOs
```
mkdir build
cd build
cmake ..
make
```

## Windows
```
mkdir build
cd build
cmake ..
cmake --build .
```
If you want to generate compile_commands.json on windows you need to  build
ninja.

```
cmake -G Ninja ..
```

