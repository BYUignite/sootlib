####################### EXAMPLES ###############################

if(SOOTLIB_BUILD_EXAMPLES_BASIC)
    # ---- simple example executable ----
    add_executable(simple_example simple_example.cc)
    target_link_libraries(simple_example PRIVATE sootModel)
    target_include_directories(simple_example PRIVATE "../../src")

    # ---- simple example installation ----
    install(TARGETS simple_example
            DESTINATION "${CMAKE_CURRENT_LIST_DIR}")

endif()

if (SOOTLIB_BUILD_EXAMPLES_ADVANCED)

    find_package(Threads REQUIRED)

    # ---- Get Cantera ----
    FetchContent_Declare(cantera
            GIT_REPOSITORY https://github.com/Cantera/cantera
            GIT_TAG b0bace78223959cd3e5a15317734cacff7b0b0a2)           # cantera-2.5.1

    # ---- Add Cantera to build ----
    message(STATUS "Looking for Cantera")
    list(APPEND CMAKE_MESSAGE_INDENT "    ")

    if (SOOTLIB_SYSTEM_CANTERA)
        find_package(cantera REQUIRED)      # throws an error if required package not found
        if (cantera_FOUND)
            message(STATUS "Using system installation of Cantera")
        endif ()
    endif ()

    if (NOT SOOTLIB_SYSTEM_CANTERA OR NOT cantera_FOUND)
        FetchContent_GetProperties(cantera)
        if (NOT cantera_POPULATED)
            FetchContent_Populate(cantera)
        endif()
        ExternalProject_Add(cantera
                SOURCE_DIR  ${cantera_SOURCE_DIR}
                BINARY_DIR  ${cantera_SOURCE_DIR}
                CONFIGURE_COMMAND ""
                BUILD_COMMAND scons build python_package=n matlab_toolbox=n f90_interface=n googletest=none prefix=${CMAKE_SOURCE_DIR} system_sundials=n boost_inc_dir=${Boost_INCLUDE_DIR} system_yamlcpp=n
                INSTALL_COMMAND scons install
                )
        message(STATUS "Using Cantera fetched from repository")
    endif()

    file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/include)

    add_library(cantera-ext SHARED IMPORTED GLOBAL)
    set_target_properties(cantera-ext PROPERTIES
            IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libcantera.a
            IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/lib/libcantera.a
            INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/include
            )

    list(POP_BACK CMAKE_MESSAGE_INDENT)

    get_target_property(cantera_INCLUDE_DIR cantera-ext INTERFACE_INCLUDE_DIRECTORIES)  # tell CMake where to find cantera headers

    # ---- Advanced example executable ----
    add_executable(advanced_example advanced_example.cc)
    target_include_directories(advanced_example PRIVATE "${PROJECT_SOURCE_DIR}/src" ${cantera_INCLUDE_DIR})
    target_link_libraries(advanced_example PRIVATE sootModel cantera-ext Threads::Threads -pthread)

    # ---- Advanced example install ----
    install(TARGETS advanced_example
            DESTINATION "${CMAKE_CURRENT_LIST_DIR}")

endif ()