file(GLOB headers ./**.hpp)
file(GLOB sources ./**.cpp)

set(SOURCE_FILES
    ${headers}
    ${sources}
)

add_definitions(${GTK3_CFLAGS_OTHER})
link_directories(${GTK3_LIBRARY_DIRS})
set(EXE_SOURCES ${SOURCE_FILES})

include_directories(${GTK3_INCLUDE_DIRS})
add_executable(${EXECUTABLE_TEST} ${EXE_SOURCES})

target_include_directories(${EXECUTABLE_TEST} PRIVATE ${GTK3_INCLUDE_DIRS})
target_link_libraries(${EXECUTABLE_TEST} ${GTK3_LIBRARIES})