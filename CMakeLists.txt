cmake_minimum_required(VERSION 3.16)

set(SOURCE main.cpp)
set(CONIO_LIB lib/conio.cpp)
set(HERO_LIB lib/hero.cpp)
set(INTERFACE_LIB lib/interface.cpp)

add_library(conio ${CONIO_LIB})
add_library(hero ${HERO_LIB})
add_library(interface ${INTERFACE_LIB})

add_executable(game ${SOURCE})

target_link_libraries(hero conio interface)
target_link_libraries(game hero interface)
