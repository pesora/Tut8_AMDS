################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/bq34z100.c \
../Lib/buzzer.c \
../Lib/fan_control.c \
../Lib/hih8131.c \
../Lib/max7219.c \
../Lib/udp_server.c 

OBJS += \
./Lib/bq34z100.o \
./Lib/buzzer.o \
./Lib/fan_control.o \
./Lib/hih8131.o \
./Lib/max7219.o \
./Lib/udp_server.o 

C_DEPS += \
./Lib/bq34z100.d \
./Lib/buzzer.d \
./Lib/fan_control.d \
./Lib/hih8131.d \
./Lib/max7219.d \
./Lib/udp_server.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/%.o Lib/%.su Lib/%.cyclo: ../Lib/%.c Lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"D:/Sunshine/Tut8_AMDS/workspace/Portable/P101.AMDS_Portable_first_creation_on_Prototype_Board/User" -I"D:/Sunshine/Tut8_AMDS/workspace/Portable/P101.AMDS_Portable_first_creation_on_Prototype_Board/Utils" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I"D:/Sunshine/Tut8_AMDS/workspace/Portable/P101.AMDS_Portable_first_creation_on_Prototype_Board/Lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Lib

clean-Lib:
	-$(RM) ./Lib/bq34z100.cyclo ./Lib/bq34z100.d ./Lib/bq34z100.o ./Lib/bq34z100.su ./Lib/buzzer.cyclo ./Lib/buzzer.d ./Lib/buzzer.o ./Lib/buzzer.su ./Lib/fan_control.cyclo ./Lib/fan_control.d ./Lib/fan_control.o ./Lib/fan_control.su ./Lib/hih8131.cyclo ./Lib/hih8131.d ./Lib/hih8131.o ./Lib/hih8131.su ./Lib/max7219.cyclo ./Lib/max7219.d ./Lib/max7219.o ./Lib/max7219.su ./Lib/udp_server.cyclo ./Lib/udp_server.d ./Lib/udp_server.o ./Lib/udp_server.su

.PHONY: clean-Lib

