################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/touch/BL6133/bl6133.c 

C_DEPS += \
./Drivers/touch/BL6133/bl6133.d 

OBJS += \
./Drivers/touch/BL6133/bl6133.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/touch/BL6133/%.o Drivers/touch/BL6133/%.su Drivers/touch/BL6133/%.cyclo: ../Drivers/touch/BL6133/%.c Drivers/touch/BL6133/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../Core/Inc -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Drivers/audio -I../Drivers/BLE -I../Drivers/BLE/stm32wb_at -I../Drivers/CatM1 -I../Drivers/pmic -I../Drivers/pmic/MAX20303 -I../Drivers/ST7789 -I../Drivers/touch/BL6133 -I../Drivers/sensorhub -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-touch-2f-BL6133

clean-Drivers-2f-touch-2f-BL6133:
	-$(RM) ./Drivers/touch/BL6133/bl6133.cyclo ./Drivers/touch/BL6133/bl6133.d ./Drivers/touch/BL6133/bl6133.o ./Drivers/touch/BL6133/bl6133.su

.PHONY: clean-Drivers-2f-touch-2f-BL6133

