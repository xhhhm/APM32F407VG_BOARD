################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../libraries/APM32F4xx_Library/Device/Geehy/APM32F4xx/Source/gcc/startup_apm32f40x.s 

OBJS += \
./libraries/APM32F4xx_Library/Device/Geehy/APM32F4xx/Source/gcc/startup_apm32f40x.o 

S_DEPS += \
./libraries/APM32F4xx_Library/Device/Geehy/APM32F4xx/Source/gcc/startup_apm32f40x.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/APM32F4xx_Library/Device/Geehy/APM32F4xx/Source/gcc/%.o: ../libraries/APM32F4xx_Library/Device/Geehy/APM32F4xx/Source/gcc/%.s
	arm-none-eabi-gcc -x assembler-with-cpp -Xassembler -mimplicit-it=thumb -c -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -x assembler-with-cpp -Wa,-mimplicit-it=thumb  -gdwarf-2 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

