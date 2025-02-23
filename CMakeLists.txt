cmake_minimum_required(VERSION 3.30)

project(cpp_covid19_simulator VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

set(custom_sfml_2_6_2 /usr/local/Cellar/sfml@2/2.6.2)
set(custom_sfml_2_6_2_include ${custom_sfml_2_6_2}/include)
set(custom_sfml_2_6_2_lib ${custom_sfml_2_6_2}/lib)

find_package(SFML 2.6.2 REQUIRED
            HINTS ${custom_sfml_2_6_2}/lib/cmake
            COMPONENTS system window graphics network audio)

add_subdirectory(simulation)