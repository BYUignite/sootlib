# Building SootLib

--------------------------------------------------------------
## Dependencies

The code is intended to be built on Linux and MacOS systems (or the Linux subsystem for Windows).

Required software:
* C++11 or higher
* CMake 3.15+

Optional software for testing:
* Catch2 (installation automated by SootLib package)

Optional software for building documentation:
* Doxygen
* graphviz

## Build instructions

1. Create a directory ```build``` and navigate to it.
2. Run CMake: ```cmake ..```
3. Build SootLib: ```make```
4. Install SootLib: ```make install```
5. (OPTIONAL) Build documentation: ```make docs```
6. (CLEANUP) Clean build files: run ```git clean -d -f -x``` from top-level directory

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