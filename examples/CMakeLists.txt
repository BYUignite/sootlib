####################### EXAMPLES ###############################

add_executable(simple_example simple_example.cc)
target_link_libraries(simple_example PRIVATE sootModel)
target_include_directories(simple_example PRIVATE "${PROJECT_SOURCE_DIR}/src")

install(TARGETS simple_example
        DESTINATION "${CMAKE_CURRENT_LIST_DIR}")


###############################################################################

add_executable(burner_flame burner_flame/burner_flame.cc burner_flame/interp_linear.h)
target_link_libraries(burner_flame PRIVATE sootModel)
target_include_directories(burner_flame PRIVATE "${PROJECT_SOURCE_DIR}/src")

install(TARGETS burner_flame
        DESTINATION "${CMAKE_CURRENT_LIST_DIR}/burner_flame")
