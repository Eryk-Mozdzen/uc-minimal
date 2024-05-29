cmake_minimum_required(VERSION 3.16)

set(CMAKE_TOOLCHAIN_FILE "toolchain.cmake")

project(atmega328p-c)

set(TARGET ${CMAKE_PROJECT_NAME}.elf)

add_executable(${TARGET}
	"src/main.c"
)

target_include_directories(${TARGET} PRIVATE
	"include"
)

target_compile_options(${TARGET} PRIVATE
	-Os
	-Wall
	-Wextra
	-Wpedantic
	-mmcu=atmega328p
)

target_compile_definitions(${TARGET} PRIVATE
	F_CPU=8000000UL
)

target_link_options(${TARGET} PRIVATE
	-Wl,-Map=${CMAKE_PROJECT_NAME}.map
	-mmcu=atmega328p
)

add_custom_command(
	TARGET ${TARGET} POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O ihex ${TARGET} ${CMAKE_PROJECT_NAME}.hex
	COMMAND ${CMAKE_OBJDUMP} -j .text -D ${TARGET} > ${CMAKE_PROJECT_NAME}.dump
	COMMAND ${CMAKE_SIZE} ${TARGET}
)

add_custom_target(flash
	avrdude -p m328p -c usbasp -e -U flash:w:${CMAKE_PROJECT_NAME}.hex:i
	DEPENDS ${TARGET}
)
