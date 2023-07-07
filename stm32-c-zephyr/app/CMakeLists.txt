cmake_minimum_required(VERSION 3.20.0)

set(BOARD "nucleo_f411re")

find_package(Zephyr)

project(stm32-c-zephyr)

target_sources(app PRIVATE
	"src/main.c"
)
