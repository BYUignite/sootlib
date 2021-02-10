Josh's branch of sootlib

this is not guarenteed to be stable at all and probably won't build sometimes

# Build Requirments

Sootlib requires C++17

Sootlib can be built without any optional dependencies by turning off Cantera compatability and not building tests.

Google Test: The unit tests in `test/` require Google Test to be built. Google Test is currently included in this
directory. https://github.com/google/googletest

Cantera: To build the Cantera compat components of the library and any tests or examples that require Cantera, you need
Cantera installed as a system library. https://cantera.org/install/index.html

# Build options

In the top level `CMakeLists.txt` you can enable/disable `BUILD_CANTERA_COMPAT`. This will:
* Determine if Cantera examples will build (if examples are set to be built)
* Determine if Cantera tests will be built (if tests are set to be built)
* Determine if Cantera integration elements of sootlib are built and included in the library

In the top level `CMakeLists.txt` you can enable/disable `BUILD_TESTS`. This will:
* Determine if gtest tests are built

In the top level `CMakeLists.txt` you can enable/disable `BUILD_EXAMPLES`. This will:
* Determine if examples are built

You can add .cpp source files to `example/standard/` and `example/cantera/`. Add these files to either
`example/standard/CMakeLists.txt` or `example/cantera/CMakeLists.txt` depending on if they require Cantera. Add
`example_src.cpp` as `example_src`. These files will be built as standalone executables.

You can add .cpp source files to `test/standard` and `test/cantera`. Add these files to either
`test/standard/CMakeLists.txt` or `test/cantera/CMakeLists.txt` depngind on if they required Cantera. Add
`example_test.cpp` as `example_test`. These files will be built as standalone executables with Google Test. Files in
`test/standard/` will be added to the test list `standardTests`. Files in `test/cantera` will be added to the test list
`canteraTests`.

# TODO

### Short Term Design

* Determine role of `sootvar` object from original code. If it's being used as a random collection of values that needs
  to change.
* Determine role of `MomentSootState` object
* Determine desired Cantera compatability features, ex. conversion between IdealGasMix and GasState - IdealGasMix is 
  depreciated and it looks like modern Cantera usage is different than in old examples so desired functionality needs to
  be determined
* Write script/guide for running tests once they're built
  
### Long Term Design

* Docstrings are going to need to be updated
* Optimized higher dimentional models

### Broken

* Building tests is broken on Mac (M1 and x86)

### Untested

* `GasState`
* `GrowthModel_LIN`
* `GrowthModel_LL`
* `GrowthModel_HACA`
* `NucleationModel_LIN`
* `NucleationModel_LL`
* `OxidationModel_LL`
* `OxidationModel_LEE_NEOH`
* `OxidationModel_NSC_NEOH`
* `OxidationModel_HACA`

### Not Implemented

* `CoagulationModel_Frenk`
* `CoagulationModel_Fuchs`
* `CoagulationModel_LL`
* `NucleationModel_PAH`
* `SootModel_MONO`

### Missing Features

* `SootModel_LOGN`
* `SootModel_MOMIC`
* `SootModel_QMOM`
* `SootModel_SECT`
* `cantera_compat`
