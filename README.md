Josh's branch of sootlib

this is not guarenteed to be stable at all and probably won't build sometimes

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
