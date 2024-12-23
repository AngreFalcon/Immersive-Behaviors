# Immersive Behaviors

SKSE64 plugin implementing context-aware behaviors for improved immersion and convenience.
Currently includes:
* a behavior to automatically shift between running and walking
* a behavior to automatically switch between first person and third person.
* an improvement to sprint key, allowing the player to run while walking for as long as the key is held (does not affect sprinting while running)

Thanks to qudix for their xmake SKSE template here: https://github.com/qudix/commonlibsse-ng-template.git

### Requirements
* [XMake](https://xmake.io) [2.8.2+]
* C++23 Compiler (MSVC, Clang?)

## Getting Started
```bat
git clone --recurse-submodules https://github.com/AngreFalcon/Immersive-Behaviors.git
cd Immersive-Behaviors
```

### Build
To build the project, run the following command:
```bat
xmake build
```

> ***Note:*** *This will generate a `build/windows/` directory in the **project's root directory** with the build output.*

### Build Output (Optional)
If you want to redirect the build output, set one of or both of the following environment variables:

- Path to a Skyrim install folder: `XSE_TES5_GAME_PATH`

- Path to a Mod Manager mods folder: `XSE_TES5_MODS_PATH`

### Project Generation (Optional)
If you want to generate a Visual Studio project, run the following command:
```bat
xmake project -k vsxmake
```

> ***Note:*** *This will generate a `vsxmakeXXXX/` directory in the **project's root directory** using the latest version of Visual Studio installed on the system.*

### Upgrading Packages (Optional)
If you want to upgrade the project's dependencies, run the following commands:
```bat
xmake repo --update
xmake require --upgrade
```

## Documentation
Please refer to the [Wiki](../../wiki/Home) for more advanced topics.
