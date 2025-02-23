project(simulation)

set(sources src/location.cpp 
            src/main.cpp 
            src/mobility_model.cpp 
            src/person.cpp
            src/ppmodel.cpp)

set(includes include/)

add_definitions(${GTK3_CFLAGS_OTHER})
link_directories(${GTK3_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC ${includes} ${GTK3_INCLUDE_DIRS} ${custom_sfml_2_6_2_include})
target_link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES} sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
