####################### EXAMPLES ###############################

add_executable(sootlibExamples simple_example.cc)
target_link_libraries(sootlibExamples PRIVATE sootModel)
target_include_directories(sootlibExamples PRIVATE "${PROJECT_SOURCE_DIR}/src")

install(TARGETS sootlibExamples
        DESTINATION "${CMAKE_CURRENT_LIST_DIR}")