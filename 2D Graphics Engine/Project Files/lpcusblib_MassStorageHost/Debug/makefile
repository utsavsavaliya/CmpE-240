################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include lpcusblib/Drivers/USB/Core/HCD/OHCI/subdir.mk
-include lpcusblib/Drivers/USB/Core/HCD/subdir.mk
-include lpcusblib/Drivers/USB/Core/HAL/LPC17XX/subdir.mk
-include lpcusblib/Drivers/USB/Core/subdir.mk
-include lpcusblib/Drivers/USB/Class/Host/subdir.mk
-include lpcusblib/Drivers/USB/Class/Common/subdir.mk
-include fatfs/src/subdir.mk
-include example/src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := lpcusblib_MassStorageHost
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: lpcusblib_MassStorageHost.axf

# Tool invocations
lpcusblib_MassStorageHost.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\Checkout\Documents\MCUXpressoIDE_11.6.0_8187\workspace\lpc_chip_175x_6x\Debug" -L"C:\Users\Checkout\Documents\MCUXpressoIDE_11.6.0_8187\workspace\lpc_board_nxp_lpcxpresso_1769\Debug" -Xlinker -Map="lpcusblib_MassStorageHost.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "lpcusblib_MassStorageHost_Debug.ld" -o "lpcusblib_MassStorageHost.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) lpcusblib_MassStorageHost.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "lpcusblib_MassStorageHost.axf"; # arm-none-eabi-objcopy -v -O binary "lpcusblib_MassStorageHost.axf" "lpcusblib_MassStorageHost.bin" ; # checksum -p LPC1769 -d "lpcusblib_MassStorageHost.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
