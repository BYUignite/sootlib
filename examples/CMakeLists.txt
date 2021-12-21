####################### EXAMPLES ###############################

add_executable(sootlibExamples simple_example.cc)

target_link_libraries(sootlibExamples PRIVATE sootlib)

target_include_directories(sootlibExamples PRIVATE "${PROJECT_SOURCE_DIR}/src")