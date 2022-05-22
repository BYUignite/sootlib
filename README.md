# Building SootLib

--------------------------------------------------------------
## Dependencies

The code is intended to be built on Linux and MacOS systems (or the Linux subsystem for Windows).

Required:
* C++11
* CMake 3.15+

Testing (optional):
* Catch2 (can be locally installed via CMake)

Examples (optional):
* Cantera 2.5.1 (can be locally installed via CMake)

Documentation (optional):
* Doxygen
* graphviz

## Build instructions

If working from the command line, first create a `build` directory and navigate into it. From there, build as follows:
1. Configure CMake: `cmake ..`
2. Build SootLib: `make`
3. Install SootLib: `make install`
4. Clean build files: run ```git clean -d -f -x``` from top-level directory

To build documentation (optional)
5. Build documentation: ```make docs```


## Build options
Build options are located under the ```PROJECT OPTIONS``` heading in the top-level ```CMakeLists.txt``` file. They can also be specified from the command line during the CMake configuration step.

| Option               | Default value                 | Function                        |
|----------------------|-------------------------------|---------------------------------|
| ```CMAKE_INSTALL_PREFIX``` | ```${PROJECT_SOURCE_DIR}/installed``` | Specifies installation location |
| ```BUILD_EXAMPLES```       | ```ON```                            | Builds SootLib examples         |
| ```BUILD_TESTS```          | ```ON```                            | Builds SootLib tests            |
| ```BUILD_DOCS```           | ```ON```                            | Builds SootLib documentation    |

## Default installation locations

* C++
    * library: ```libsootlib.a``` is located in ```installed/lib```
    * header files: ```constants.h```, ```sootModel.h```, and ```state.h``` are located in ```installed/include```
* CMake
    * Relocatable package ```sootlib.cmake``` is located in ```installed/cmake/sootlib```