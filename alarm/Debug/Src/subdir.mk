################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Accelerometer.c \
../Src/GSM.c \
../Src/debug.c \
../Src/freertos.c \
../Src/gpio.c \
../Src/gps.c \
../Src/i2c.c \
../Src/main.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c \
../Src/tim.c \
../Src/usart.c 

OBJS += \
./Src/Accelerometer.o \
./Src/GSM.o \
./Src/debug.o \
./Src/freertos.o \
./Src/gpio.o \
./Src/gps.o \
./Src/i2c.o \
./Src/main.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o \
./Src/tim.o \
./Src/usart.o 

C_DEPS += \
./Src/Accelerometer.d \
./Src/GSM.d \
./Src/debug.d \
./Src/freertos.d \
./Src/gpio.d \
./Src/gps.d \
./Src/i2c.d \
./Src/main.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d \
./Src/tim.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F417xx -I"/home/flisu/STM32/alarm/Inc" -I"/home/flisu/STM32/alarm/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/flisu/STM32/alarm/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/home/flisu/STM32/alarm/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/flisu/STM32/alarm/Drivers/CMSIS/Include" -I"/home/flisu/STM32/alarm/Inc" -I"/home/flisu/STM32/alarm/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/flisu/STM32/alarm/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/flisu/STM32/alarm/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


