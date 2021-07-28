####################### TESTING ###############################

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

add_executable(sootlibTests constantsTests.cc
                            stateTests.cc
                            sootModelTests.cc)

target_link_libraries(sootlibTests PRIVATE Catch2::Catch2 sootlib)

target_include_directories(sootlibTests PRIVATE "${CMAKE_SOURCE_DIR}/src")

#add_subdirectory(stateTests)
#add_subdirectory(sootModelTests)
#add_subdirectory(psdModelsTests)
#add_subdirectory(sootChemistryTests)


