# Build Requirments

Sootlib requires C++17

# Build Instructions

Run `cmake .` to generate the sootlib build files in the current directory while inside of the top level sootlib directory.

This will generate the necessary Makefiles and you can now run `make` to build the project.

Use the options described below to customize your build. If you run `cmake .` and then change your build options, you will
need to either delete `CMakeCache.txt` or ensure that you have removed the cached values you changed.

# Build options

In the top level `CMakeLists.txt` you can enable/disable `BUILD_TESTS`. This will:
* Determine if gtest tests are built
* To build tests on Mac you need Google Test installed system wide

In the top level `CMakeLists.txt` you can enable/disable `BUILD_EXAMPLES`. This will:
* Determine if examples are built

You can add .cc source files to `example/`. Add these files to
`example/CMakeLists.txt`. Add
`example_src.cc` as `example_src`. These files will be built as standalone executables.

You can add .cc source files to `test/tests/`. Add these files to
`test/tests/CMakeLists.txt` . Add
`example_test.cc` as `example_test`. These files will be built as standalone executables with Google Test. Files in
`test/tests/` will be added to the test list `standardTests`.

We should roughly follow the [Cantera contributions stype guide](https://github.com/Cantera/cantera/blob/main/CONTRIBUTING.md)
in this project.

# TODO

### Short Term Design

* Perhaps add warnings when running into 0 or having illegal calculations to guide people in NAN situations
  
### Long Term Design

* Optimized higher dimentional models
* Determine needed state constructor / generator features

### Broken / Not Building

* SECT model was highly broken in old code so current interpretation is probably not accurate
* MOMIC throws vector out of bounds errors in all situations
