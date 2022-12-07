# SootLib overview

[Sootlib](https://github.com/BYUignite/sootlib.git) is an open-source C++ library that computes soot source terms using moment-based particle size distribution models for combustion CFD simulations.

# Dependencies and installation

The code is intended to be built and used on Linux-like systems, including MacOS and the Linux subsystem for Windows.

Required software:
* CMake 3.15+
* C++11

Optional software:
* Doxygen (for building documentation)
* graphviz (for Doxygen)
* Catch2 (for building tests; will be locally installed automatically via CMake if `SOOTLIB_BUILD_TESTS` is true)

## Build and installation instructions
1. Create and navigate into a top-level `build` directory
2. Configure CMake: `cmake ..`
3. Build SootLib: `make`
4. Install SootLib: `make install`

## CMake configuration variables
The default CMake configuration should be adequate for users that do not immediately require the examples, tests, or documentation. CMake configuration options can be set by editing the top-level `CMakeLists.txt` file, editing the `CMakeCache.txt` file (generated in the `build` directory after running CMake at least once), or specifying them on the command line during step 2 as follows:
```
cmake -DSOOTLIB_BUILD_EXAMPLES=ON ..
```

The following project-specific CMake configuration variables can be specified by the user; their default values are also indicated.
* `CMAKE_INSTALL_PREFIX = ..\`     Installation location 
* `SOOTLIB_BUILD_EXAMPLES = OFF`  Builds SootLib examples 
* `SOOTLIB_BUILD_TESTING = OFF`  Builds SootLib tests; uses Catch2 
* `SOOTLIB_BUILD_DOCS = OFF`  Builds SootLib documentation via Doxygen 

# Using SootLib

The SootLib library consists of two main object classes that users can interact with: `sootModel` and `state`, both of which are contained within the `soot` namespace. The `state` object holds user-specified details about the current thermodynamic state in which the soot chemistry occurs, including variables such as temperature, pressure, and gas species mass fractions. The `sootModel` object contains information about the selected models and mechanisms and performs the calculations that generate moment source terms. In the context of a traditional CFD simulation, the `state` object would be updated via the `setState` function at each individual time step and/or grid point, while the `sootModel` parameters only need to be specified once when the object is created, and then its `calcSourceTerms` function invoked at each step following the `setState` update. The resulting moment source terms and gas species source terms can be accessed via the `sootModel` object. Refer to `examples/simple_example.cc` for a basic example of setting up the objects, calculating source terms, and retrieving values.

## Example workflow
1. Create `sootModel` object, specifying the desired soot chemistry and PSD mechanism.
2. Create an empty `state` object.
3. Populate the `state` object with the thermodynamic conditions using the `setState` function.
4. Calculate the soot source terms using the `calcSourceTerms` function, which takes a reference to a `state` object as its input. 
5. Retrieve the desired source terms from the `sootModel` object. 

In the case of a temporally or spatially evolving simulation, only steps 3–5 need be performed at each individual step. SootLib does not store previously calculated values, so source terms must be retrieved at each step or otherwise lost.  

