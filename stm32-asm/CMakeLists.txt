cmake_minimum_required(VERSION 3.16)

set(CMAKE_TOOLCHAIN_FILE "arm-none-eabi.cmake")

project(stm32-asm)

enable_language(ASM)

set(TARGET ${CMAKE_PROJECT_NAME}.elf)

add_executable(${TARGET}
	"src/main.s"
)

target_compile_options(${TARGET} PRIVATE
	-O0 -g

	#-mthumb
	#-mhard-float
	-mcpu=cortex-m4
	#-mfpu=fpv4-sp-d16
	#-specs=nano.specs

	-nostdlib
)

target_link_options(${TARGET} PRIVATE
	-T ${CMAKE_SOURCE_DIR}/linker.ld
	-Wl,-Map=${CMAKE_PROJECT_NAME}.map
	-Wl,--gc-sections

	-mthumb
	#-mhard-float
	#-mfloat-abi=hard
	-mcpu=cortex-m4
	#-mfpu=fpv4-sp-d16
	#-specs=nano.specs
	#-specs=nosys.specs

	#-static
)

add_custom_command(
	TARGET ${TARGET} POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O binary ${TARGET} ${CMAKE_PROJECT_NAME}.bin
	COMMAND ${CMAKE_OBJDUMP} -j .text -D ${TARGET} > ${CMAKE_PROJECT_NAME}.dump
	COMMAND ${CMAKE_SIZE} ${TARGET}
)
