set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib") # to include sootlib (built in this project)
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)           # only needed if examples dep on an external lib

###############################

#--------------- simple_example

add_executable(simple_example simple_example.cc)
target_include_directories(simple_example PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(simple_example PRIVATE sootlib)
install(TARGETS simple_example DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")

#--------------- burner_flame

add_executable(burner_flame burner_flame/burner_flame.cc)
target_include_directories(burner_flame PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(burner_flame PRIVATE sootlib)
install(TARGETS burner_flame DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/burner_flame")
