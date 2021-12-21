####################### TESTING ###############################

include(FetchContent)

FetchContent_Declare( Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.1)
FetchContent_MakeAvailable(Catch2)

add_executable(sootlibTests constantsTests.cc
                            stateTests.cc
                            sootModelTests.cc
                            psdModelTests.cc
                            nucleationModelTests.cc
                            growthModelTests.cc
                            oxidationModelTests.cc
                            coagulationModelTests.cc)

target_link_libraries(sootlibTests PRIVATE Catch2::Catch2 sootlib)
target_include_directories(sootlibTests PRIVATE "${PROJECT_SOURCE_DIR}/src")