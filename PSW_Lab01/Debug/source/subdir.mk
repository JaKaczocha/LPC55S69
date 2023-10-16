################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/PSW_Lab01.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/PSW_Lab01.d \
./source/semihost_hardfault.d 

OBJS += \
./source/PSW_Lab01.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DCPU_LPC55S69JBD100_cm33_core0 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\User\Desktop\LPC55S69\LPC55S69\PSW_Lab01\board" -I"C:\Users\User\Desktop\LPC55S69\LPC55S69\PSW_Lab01\source" -I"C:\Users\User\Desktop\LPC55S69\LPC55S69\PSW_Lab01\drivers" -I"C:\Users\User\Desktop\LPC55S69\LPC55S69\PSW_Lab01\device" -I"C:\Users\User\Desktop\LPC55S69\LPC55S69\PSW_Lab01\CMSIS" -I"C:\Users\User\Desktop\LPC55S69\LPC55S69\PSW_Lab01\utilities" -I"C:\Users\User\Desktop\LPC55S69\LPC55S69\PSW_Lab01\component\uart" -I"C:\Users\User\Desktop\LPC55S69\LPC55S69\PSW_Lab01\component\serial_manager" -I"C:\Users\User\Desktop\LPC55S69\LPC55S69\PSW_Lab01\component\lists" -I"C:\Users\User\Desktop\LPC55S69\LPC55S69\PSW_Lab01\startup" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/PSW_Lab01.d ./source/PSW_Lab01.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

