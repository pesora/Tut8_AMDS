################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/collect.c \
../User/debug_uart.c \
../User/display.c \
../User/process.c \
../User/send.c \
../User/udp_protocol.c \
../User/user_timer.c 

OBJS += \
./User/collect.o \
./User/debug_uart.o \
./User/display.o \
./User/process.o \
./User/send.o \
./User/udp_protocol.o \
./User/user_timer.o 

C_DEPS += \
./User/collect.d \
./User/debug_uart.d \
./User/display.d \
./User/process.d \
./User/send.d \
./User/udp_protocol.d \
./User/user_timer.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o User/%.su User/%.cyclo: ../User/%.c User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"D:/Sunshine/Tut8_AMDS/workspace/Portable/P101.AMDS_Portable_first_creation_on_Prototype_Board/User" -I"D:/Sunshine/Tut8_AMDS/workspace/Portable/P101.AMDS_Portable_first_creation_on_Prototype_Board/Utils" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I"D:/Sunshine/Tut8_AMDS/workspace/Portable/P101.AMDS_Portable_first_creation_on_Prototype_Board/Lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User

clean-User:
	-$(RM) ./User/collect.cyclo ./User/collect.d ./User/collect.o ./User/collect.su ./User/debug_uart.cyclo ./User/debug_uart.d ./User/debug_uart.o ./User/debug_uart.su ./User/display.cyclo ./User/display.d ./User/display.o ./User/display.su ./User/process.cyclo ./User/process.d ./User/process.o ./User/process.su ./User/send.cyclo ./User/send.d ./User/send.o ./User/send.su ./User/udp_protocol.cyclo ./User/udp_protocol.d ./User/udp_protocol.o ./User/udp_protocol.su ./User/user_timer.cyclo ./User/user_timer.d ./User/user_timer.o ./User/user_timer.su

.PHONY: clean-User

