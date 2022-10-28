################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fatfs/src/ff.c \
../fatfs/src/fs_usb.c \
../fatfs/src/rtc.c 

C_DEPS += \
./fatfs/src/ff.d \
./fatfs/src/fs_usb.d \
./fatfs/src/rtc.d 

OBJS += \
./fatfs/src/ff.o \
./fatfs/src/fs_usb.o \
./fatfs/src/rtc.o 


# Each subdirectory must supply rules for building sources it contributes
fatfs/src/%.o: ../fatfs/src/%.c fatfs/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -D__LPC175X_6X__ -DUSB_HOST_ONLY -DCORE_M3 -I"C:\Users\Checkout\Documents\MCUXpressoIDE_11.6.0_8187\workspace\lpc_chip_175x_6x\inc" -I"C:\Users\Checkout\Documents\MCUXpressoIDE_11.6.0_8187\workspace\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\Users\Checkout\Documents\MCUXpressoIDE_11.6.0_8187\workspace\lpcusblib_MassStorageHost\example\inc" -I"C:\Users\Checkout\Documents\MCUXpressoIDE_11.6.0_8187\workspace\lpcusblib_MassStorageHost\lpcusblib\Drivers\USB" -I"C:\Users\Checkout\Documents\MCUXpressoIDE_11.6.0_8187\workspace\lpcusblib_MassStorageHost\fatfs\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-fatfs-2f-src

clean-fatfs-2f-src:
	-$(RM) ./fatfs/src/ff.d ./fatfs/src/ff.o ./fatfs/src/fs_usb.d ./fatfs/src/fs_usb.o ./fatfs/src/rtc.d ./fatfs/src/rtc.o

.PHONY: clean-fatfs-2f-src

