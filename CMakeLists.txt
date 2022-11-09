cmake_minimum_required(VERSION 3.16)

set(GAME main.cpp)
set(GENERATOR generator.cpp)

set(CONIO_LIB lib/conio.cpp)
set(HERO_LIB lib/hero.cpp)
set(INTERFACE_LIB lib/interface.cpp)
set(ENEMY_LIB lib/enemy.cpp)

add_library(conio ${CONIO_LIB})
add_library(hero ${HERO_LIB})
add_library(interface ${INTERFACE_LIB})
add_library(enemy ${ENEMY_LIB})

add_executable(game ${GAME})
add_executable(generator ${GENERATOR})

target_link_libraries(hero conio interface)
target_link_libraries(game hero interface enemy)
target_link_libraries(generator conio)
