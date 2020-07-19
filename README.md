# Megadrive-Maze

![C CI](https://github.com/DPriceDev/Megadrive-Maze/workflows/C/C++%20CI/badge.svg)

This is a small Sega Megadrive/Genesis game project with an emphasis on running within Clion. The project is a small maze based game, hopefully with a few
monsters and weapons and such.

## Getting Started

These are the specific requirements for setting the project up with Clion as of 13th July 2020.

### Prerequisites

The main requirement for this project is Clion 2020.2 or above.

## Building

To clone this repo, use the '--recursive' flag to capture the submodule dependencies.

```
git clone --recursive https://github.com/DPriceDev/Megadrive-Maze
```

Once cloned, the project can be opened directly in Clion. There are two targets setup in the cmake "Megadrive-maze" and "dummy".
Dummy is setup to allow file discovery and is not a runnable target. The project can be built by building the Megadrive-maze cmake target.

### Building the hard way

There is a harder way to do this (my first attempt at building this before switching to cmake) by explicitly declaring make as an external tool. These instructions are here for 
posterity, as I would suggest using the Cmake project to build the project instead.

To clone this repo, use the '--recursive' flag to capture the submodule dependencies.

```
git clone --recursive https://github.com/DPriceDev/Megadrive-Maze
```

Open the repo folder in Clion. Once loaded you can begin to setup the configuration. Open the configurations dialog, 
usually shown in the top right of the IDE or from the toolbar:

```
run -> edit configurations...
```

From here you can setup the makefile configuration by going to:

```
+ (add new configuration) -> Makefile Application
name: SGDK Build
```

Now the target needs to be set, open up the custom targets panel in the settings by clicking the three dots next to the target dropdown, and 
then adding a custom target:

```
target: ... -> Settings -> Build, Excecution and deployment -> Custom Build Targets -> + (add new target)

Custom Build Target
name: SGDK Target
```

Name the target, and then for the build you are going to once again select the three dots next to the build dropdown and then
select add to add a new external tool.

```
build: ... -> external tools -> + (add external tool)
```

Once the external tool dialog appears, you are going to need to fill a few sections out, these being name, Program, arguments and working directory.
The program is going to be the make.exe that comes as part of the SGDK, the argument is the flag and path to the makefile, also from the SGDK, and the
working directory is the repo project directory.

```
name: SGDK Make
Program:            C:\...path_to_repo...\Megadrive-Maze\depends\sgdk\bin\make.exe
Arguments:          -f C:\...path_to_repo...\Megadrive-Maze\depends\sgdk\bin\makefile.gen
Working directory:  C:\...path_to_repo...\Megadrive-Maze
```

Once finished, you can create the external tool, set the custom build target as this tool, and then applying that back to the configuration tab, where it can be set as the target for the configuration. when everything
is complete and done, click create configuration (I also forget to) before closing the dialog.

```
custom build target
build: SGDK Make

configuration
name: SGDK Build
target: SGDK Target

then create configuration...
```

From here you can hit the build icon and the rom should build into the out folder.

```
out/rom.bin
```

## Deployment

Deployment is fairly easy from an emulated point of view. Once the rom has been built it can be loaded into a number of different
emulators, such as Gensk and regen. The standard gens emulator seems to have graphical issues and may not run.

The deployment can be taken further within Clion if you want it to be more automated in running the emulator. This can be done by
reopening the SGDK Build Configuration and adding the emulator parameters. In this example I am using Gensk. Simply set the executable to the
gens.exe program and set the program arguments to the path to the rom.

with external makefile tool
```
External Makefile Configuration
name: SGDK build
Target: SGDK Target
Executable: C:\..path_to_emulator..\gensk\gens.exe
Program Arguement: C:\..path_to_repo\Megadrive-Maze\out\rom.bin
```
or with cmake
```
CMake Configuration
name: Megadrive-Maze
Target: Megadrive-Maze
Executable: C:\..path_to_emulator..\gensk\gens.exe
Program Arguement: C:\..path_to_repo\Megadrive-Maze\out\rom.bin
```

Now clicking the green run arrow in the IDE will build the rom and then launch it into the emulator.

## Debugging

Debugging can be set up with the gensk emulator by connect to its GDB server with clion. Make sure you are on the debug variant of the target, 
which can be set in the configuration dropdown, and you have built "MEGADRIVE-MAZE | DEBUG" at least once.

Once you have the debug build, open the configurations, from the dropdown, or from:
```
run -> edit configurations...
```

Then create a new build configuration with Remote GDB. This configuration allows clion to connect to gensk to
allow us to debug.
```
+ (add new configuration) -> GDB Remote Debug
name: Gensk Debug
```

Finally, you can fill in the configuration with the path to the GDB debugger, located in the SGDK, and the path to the
rom.out, located in the out folder of the project.

```
CMake Configuration
name: GDB Remote Debug
GDB: C:\..path_to_emulator..\gensk\GDB.exe
'target remote' args: localhost:6868
Symbol file: C:\..path_to_repo\Megadrive-Maze\out\rom.out
```

Once created, you can run the target "MEGADRIVE-MAZE | DEBUG", and then switch to this new "GDB Remote Debug" configuration, and click
the debug button. This will connect the IDE to gensk and will allow debugging.

## Additional

The project comes with a CMakeList.txt file for compatibility with Clion; however, it does not play an active role in the build
system, and only provides IDE support for discovering includes and source files.

## Troubleshooting

If you have trouble building the Debug build, it may help to build the release first, as sometimes the debug build of sgdk doesnt create the
symbols.txt file before it is required.

## Built With

* [SGDK](https://github.com/Stephane-D/SGDK) - The Sega Genesis C Development Kit

## Authors

* **David Price** - *Initial work* - [DPriceDev](https://github.com/DPriceDev)

## License

This project is licensed under the Apache v2.0 License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Inspired by [GameHut](https://www.youtube.com/channel/UCfVFSjHQ57zyxajhhRc7i0g)
* Thankful for 8-bit the Dungeon Tileset created by [Scut](https://scut.itch.io/7drl-tileset-2018) from itch.io
