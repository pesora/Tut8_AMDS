################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utils/ema.c \
../Utils/pid.c \
../Utils/ring_buffer.c \
../Utils/utility.c 

OBJS += \
./Utils/ema.o \
./Utils/pid.o \
./Utils/ring_buffer.o \
./Utils/utility.o 

C_DEPS += \
./Utils/ema.d \
./Utils/pid.d \
./Utils/ring_buffer.d \
./Utils/utility.d 


# Each subdirectory must supply rules for building sources it contributes
Utils/%.o Utils/%.su Utils/%.cyclo: ../Utils/%.c Utils/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"D:/Sunshine/Tut8_AMDS/workspace/Portable/P101.AMDS_Portable_first_creation_on_Prototype_Board/User" -I"D:/Sunshine/Tut8_AMDS/workspace/Portable/P101.AMDS_Portable_first_creation_on_Prototype_Board/Utils" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I"D:/Sunshine/Tut8_AMDS/workspace/Portable/P101.AMDS_Portable_first_creation_on_Prototype_Board/Lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Utils

clean-Utils:
	-$(RM) ./Utils/ema.cyclo ./Utils/ema.d ./Utils/ema.o ./Utils/ema.su ./Utils/pid.cyclo ./Utils/pid.d ./Utils/pid.o ./Utils/pid.su ./Utils/ring_buffer.cyclo ./Utils/ring_buffer.d ./Utils/ring_buffer.o ./Utils/ring_buffer.su ./Utils/utility.cyclo ./Utils/utility.d ./Utils/utility.o ./Utils/utility.su

.PHONY: clean-Utils

