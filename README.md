# physic-project #
--------
physic project is a engine for creating engine with physic elements with using rendering interface of specified rendering API. Where the rendering and the physic are modules in the since that they can be replaced as a plugin.

## Motivation ##
----
The project was created in order to allow one to create a physic engine and use the program in order visually debug if the physic engine works as accordinly. This was done for a course where the assignmnet where to create a simple 3D physic engine.

# Installation #
----
The follwing how to install the program on Linux based operating systems.
## Linux ##
The program is installed with the following commands. This will create a makefile for which can be excuted by simply invoking the make command. see following. This will compile the PVEngine and all the executable. Where it will generate shader collection object for all the default shaders. All the headers, library, excutable and shared data will be installed onto the system.
```
cmake .
make
make install
```
## Windows ##

## OS-X ##

# Examples #
----

## Dependencies ##
----------------
In order to compile the program, the following Debian packages has to be installed.
```
apt-get install libzip-dev liblz4-dev libxml2-dev libassimp-dev libbullet-dev libsdl2-dev libssl-dev libvulkan-dev libfreeimage-dev
```

## License ##
This project is licensed under the GPL+3 License - see the [LICENSE](LICENSE) file for details.

