####################### EXAMPLES ###############################

add_executable(simple_example simple_example.cc)
target_link_libraries(simple_example PRIVATE sootModel)
target_include_directories(simple_example PRIVATE "${PROJECT_SOURCE_DIR}/src")

install(TARGETS simple_example
        DESTINATION "${CMAKE_CURRENT_LIST_DIR}")
