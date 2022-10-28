################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lpcusblib/Drivers/USB/Core/HCD/HCD.c 

C_DEPS += \
./lpcusblib/Drivers/USB/Core/HCD/HCD.d 

OBJS += \
./lpcusblib/Drivers/USB/Core/HCD/HCD.o 


# Each subdirectory must supply rules for building sources it contributes
lpcusblib/Drivers/USB/Core/HCD/%.o: ../lpcusblib/Drivers/USB/Core/HCD/%.c lpcusblib/Drivers/USB/Core/HCD/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -D__LPC175X_6X__ -DUSB_HOST_ONLY -DCORE_M3 -I"C:\Users\Checkout\Documents\MCUXpressoIDE_11.6.0_8187\workspace\lpc_chip_175x_6x\inc" -I"C:\Users\Checkout\Documents\MCUXpressoIDE_11.6.0_8187\workspace\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\Users\Checkout\Documents\MCUXpressoIDE_11.6.0_8187\workspace\lpcusblib_KeyboardHost\lpcusblib\Drivers\USB" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-lpcusblib-2f-Drivers-2f-USB-2f-Core-2f-HCD

clean-lpcusblib-2f-Drivers-2f-USB-2f-Core-2f-HCD:
	-$(RM) ./lpcusblib/Drivers/USB/Core/HCD/HCD.d ./lpcusblib/Drivers/USB/Core/HCD/HCD.o

.PHONY: clean-lpcusblib-2f-Drivers-2f-USB-2f-Core-2f-HCD

