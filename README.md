# peC

A simple 2D physics engine in written in C.

## Cloning, Compiling and Running

To clone the repository, run:
```console
> git clone --recurse-submodules https://github.com/rhdcc/pec.git
```

**NOTE: [CMake](https://cmake.org/) must be installed on your machine to build `pec` for all of the following build targets.**

### Windows

To build `pec`, run `build.bat` inside a Visual Studio 2019/2022 Developper Command Prompt.\
Learn more about that [here](https://learn.microsoft.com/en-us/visualstudio/ide/reference/command-prompt-powershell?view=vs-2022).

To run `pec`, just run the `pec.exe` file inside the created `bin` directory. For example, run:
```console
> bin\pec.exe
```

### Windows (MINGW32 or MSYS2) / Linux

Coming soon...

## Dependencies
 - [GLFW](https://www.glfw.org/)
 - [glad](https://github.com/dav1dde/glad-web)
 - [cglm](https://github.com/recp/cglm)
 - [CMake](https://cmake.org/)