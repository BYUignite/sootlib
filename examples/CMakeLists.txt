set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib") # to include sootlib (built in this project)
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)           # only needed if examples dep on an external lib

###############################

#--------------- simple_example

add_executable(simple_example simple_example.cc)
target_include_directories(simple_example PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(simple_example PRIVATE sootlib)
install(TARGETS simple_example DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")

#--------------- simple_example_HMOM

add_executable(simple_example_HMOM simple_example_HMOM.cc)
target_include_directories(simple_example_HMOM PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(simple_example_HMOM PRIVATE sootlib)
install(TARGETS simple_example_HMOM DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")

#--------------- burner_flame

add_executable(burner_flame burner_flame/burner_flame.cc)
target_include_directories(burner_flame PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(burner_flame PRIVATE sootlib)
install(TARGETS burner_flame DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/burner_flame")

#--------------- burner_flame_HMOM

add_executable(burner_flame_HMOM burner_flame/burner_flame_HMOM.cc)
target_include_directories(burner_flame_HMOM PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(burner_flame_HMOM PRIVATE sootlib)
install(TARGETS burner_flame_HMOM DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/burner_flame")

#--------------- burner_flame_MOMIC

add_executable(burner_flame_MOMIC burner_flame/burner_flame_MOMIC.cc)
target_include_directories(burner_flame_MOMIC PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(burner_flame_MOMIC PRIVATE sootlib)
install(TARGETS burner_flame_MOMIC DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/burner_flame")

#--------------- burner_flame_tar

add_executable(burner_flame_tar burner_flame/burner_flame_tar.cc)
target_include_directories(burner_flame_tar PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(burner_flame_tar PRIVATE sootlib)
install(TARGETS burner_flame_tar DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/burner_flame")
