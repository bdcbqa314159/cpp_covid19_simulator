project(simulation)

file(GLOB toCompile ./**.cpp)

set(sources ${toCompile})

add_definitions(${GTK3_CFLAGS_OTHER})
link_directories(${GTK3_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC ${GTK3_INCLUDE_DIRS} ${custom_sfml_2_6_2_include})
target_link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES} sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
