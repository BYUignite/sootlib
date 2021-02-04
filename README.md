Josh's branch of sootlib

this is not guarenteed to be stable at all and probably won't build sometimes

# Build Requirments

Sootlib can be built without any optional dependencies by turning off Cantera compatability and not building tests.

Google Test: The unit tests in test/ require Google Test to be built. Google Test is currently included in this
directory. https://github.com/google/googletest

Cantera: To build the Cantera compat components of the library and any tests or examples that require Cantera, you need
Cantera installed as a system library. https://cantera.org/install/index.html

# Build options

In the top level CMakeLists.txt you can enable/disable BUILD_CANTERA_COMPAT. This will:
* Determine if Cantera examples will build (if examples are set to be built)
* Determine if Cantera tests will be built (if tests are set to be built)
* Determine if Cantera integration elements of sootlib are built and included in the library

In the top level CMakeLists.txt you can enable/disable BUILD_TESTS. This will:
* Determine if gtest tests are built

In the top level CMakeLists.txt you can enable/disable BUILD_EXAMPLES. This will:
* Determine if examples are built

In the example/ folder you can add .cpp source files to cantera/ and standard/. Files in example/cantera/ will be built 
with Cantera. After adding a .cpp file to example/cantera/ or example/standard/, you need to add it to either 
CANTERA_EXAMPLES in example/cantera/CMakeLists.txt or STANDARD_EXAMPLES in example/standard/CMakeLists.txt as 
"example_src" for the file "example_src.cpp". These files will individually be built as executables.

In the test/ folder you can add .cpp source files to cantera/ and standard/. Files in test/cantera/ will be built with 
Cantera. Files in test/standard/ and test/cantera will be built with GoogleTest as individual executables. Files in 
test/standard will be added to the test list standardTests. Files in test/cantera will be added to the test list 
canteraTests.

# TODO

### Design

* Determine role of a SootState object
* Determine parameters needed for each chemistry model
* Optimized higher dimentional models

### Broken

* Bad version of Google Test

### Not Implemented

* CoagulationModel_Frenk
* CoagulationModel_Fuchs
* CoagulationModel_LL
* GrowthModel_HACA
* GrowthModel_LIN
* GrowthModel_LL
* NucleationModel_LIN
* NucleationModel_LL
* NucleationModel_PAH
* OxidationModel_HACA
* OxidationModel_LEE_NEOH
* OxidationModel_LL
* OxidationModel_NSC_NEOH
* SootModel_MONO

### Missing Features

* SootModel_LOGN
* SootModel_MOMIC
* SootModel_QMOM
* SootModel_SECT
* cantera_compat
