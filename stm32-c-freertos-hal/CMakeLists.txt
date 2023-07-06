cmake_minimum_required(VERSION 3.16)

set(CMAKE_TOOLCHAIN_FILE "arm-none-eabi.cmake")

project(stm32-c-freertos-hal)

enable_language(C ASM)

set(TARGET ${CMAKE_PROJECT_NAME}.elf)

add_executable(${TARGET}
	"cmsis_device_f4/Source/Templates/system_stm32f4xx.c"
	"cmsis_device_f4/Source/Templates/gcc/startup_stm32f411xe.s"

	"stm32f4xx_hal_driver/Src/stm32f4xx_hal_gpio.c"
	"stm32f4xx_hal_driver/Src/stm32f4xx_hal_rcc.c"
	"stm32f4xx_hal_driver/Src/stm32f4xx_hal_pwr.c"
	"stm32f4xx_hal_driver/Src/stm32f4xx_hal_dma.c"
	"stm32f4xx_hal_driver/Src/stm32f4xx_hal_tim.c"
	"stm32f4xx_hal_driver/Src/stm32f4xx_hal_tim_ex.c"
	"stm32f4xx_hal_driver/Src/stm32f4xx_hal_flash.c"
	"stm32f4xx_hal_driver/Src/stm32f4xx_hal_flash_ex.c"
	"stm32f4xx_hal_driver/Src/stm32f4xx_hal_cortex.c"
	"stm32f4xx_hal_driver/Src/stm32f4xx_hal.c"

	"FreeRTOS-Kernel/tasks.c"
	"FreeRTOS-Kernel/queue.c"
	"FreeRTOS-Kernel/list.c"
	"FreeRTOS-Kernel/portable/GCC/ARM_CM4F/port.c"
	"FreeRTOS-Kernel/portable/MemMang/heap_4.c"

	"src/main.c"
	"src/timebase.c"
)

target_compile_definitions(${TARGET} PRIVATE
	STM32F411xE
	USE_HAL
)

target_include_directories(${TARGET} PRIVATE
	"cmsis_core/Include"
	"cmsis_device_f4/Include"
	"stm32f4xx_hal_driver/Inc"

	"FreeRTOS-Kernel/include"
	"FreeRTOS-Kernel/portable/GCC/ARM_CM4F"

	"inc"
)

target_compile_options(${TARGET} PRIVATE
$<$<COMPILE_LANGUAGE:ASM>:
		-Os -g

		-mthumb
		-mhard-float
		-mcpu=cortex-m4
		-mfpu=fpv4-sp-d16
		-specs=nano.specs

		-x assembler-with-cpp
	>

	$<$<COMPILE_LANGUAGE:C>:
		-Os -g
		-std=c17

		-Wall
		-Wpedantic
		-Wdouble-promotion

		-mthumb
		-mhard-float
		-mcpu=cortex-m4
		-mfpu=fpv4-sp-d16
		-specs=nano.specs
	>
)

target_link_options(${TARGET} PRIVATE
	-T ${CMAKE_SOURCE_DIR}/linker.ld
	-Wl,-Map=${CMAKE_PROJECT_NAME}.map
	-Wl,--gc-sections
	-Wl,-cref
	-Wl,--start-group -lc -lm -Wl,--end-group

	-mthumb
	-mhard-float
	-mfloat-abi=hard
	-mcpu=cortex-m4
	-mfpu=fpv4-sp-d16
	-specs=nano.specs
	-specs=nosys.specs

	-static
)

add_custom_command(
	TARGET ${TARGET} POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O binary ${TARGET} ${CMAKE_PROJECT_NAME}.bin
	COMMAND ${CMAKE_OBJDUMP} -j .text -D ${TARGET} > ${CMAKE_PROJECT_NAME}.dump
	COMMAND ${CMAKE_SIZE} ${TARGET}
)
