cmake_minimum_required(VERSION 3.20.0)

set(BOARD_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/.")
set(BOARD "example_board")
#set(BOARD "nucleo_f411re")

find_package(Zephyr)
project(stm32-zephyr)

target_sources(app PRIVATE 
	"src/main.c"
)
