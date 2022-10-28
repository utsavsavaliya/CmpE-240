################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include lwip/src/netif/subdir.mk
-include lwip/src/core/ipv4/subdir.mk
-include lwip/src/core/subdir.mk
-include lwip/src/arch/subdir.mk
-include lwip/src/api/subdir.mk
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


BUILD_ARTIFACT_NAME := iperf_server
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: iperf_server.axf

# Tool invocations
iperf_server.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\Checkout\Documents\MCUXpressoIDE_11.6.0_8187\workspace\lpc_chip_175x_6x\Debug" -L"C:\Users\Checkout\Documents\MCUXpressoIDE_11.6.0_8187\workspace\lpc_board_nxp_lpcxpresso_1769\Debug" -Xlinker -Map="iperf_server.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "iperf_server_Debug.ld" -o "iperf_server.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) iperf_server.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "iperf_server.axf"; # arm-none-eabi-objcopy -v -O binary "iperf_server.axf" "iperf_server.bin" ; # checksum -p LPC1769 -d "iperf_server.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
