####################### EXAMPLES ###############################

find_library(SOOTMODEL NAMES sootModel)

add_executable(simple_example simple_example.cc)
if(APPLE)
    find_library(ACCELERATE Accelerate)
    set_property(TARGET simple_example PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()
target_link_libraries(simple_example PRIVATE ${SOOTMODEL} ${ACCELERATE})
target_include_directories(simple_example PRIVATE "${PROJECT_SOURCE_DIR}/src")

install(TARGETS simple_example
        DESTINATION "${CMAKE_CURRENT_LIST_DIR}")

###############################################################################

add_executable(burner_flame burner_flame/burner_flame.cc burner_flame/interp_linear.h)
if(APPLE)
    find_library(ACCELERATE Accelerate)
    set_property(TARGET burner_flame PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()
target_link_libraries(burner_flame PRIVATE ${SOOTMODEL} ${ACCELERATE})
target_include_directories(burner_flame PRIVATE "${PROJECT_SOURCE_DIR}/src")


install(TARGETS burner_flame
        DESTINATION "${CMAKE_CURRENT_LIST_DIR}/burner_flame")
