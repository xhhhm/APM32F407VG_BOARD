################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../applications/main.c 

OBJS += \
./applications/main.o 

C_DEPS += \
./applications/main.d 


# Each subdirectory must supply rules for building sources it contributes
applications/%.o: ../applications/%.c
	arm-none-eabi-gcc -I"D:\Xhh_files\RT_Thread\APM32F407" -I"D:\Xhh_files\RT_Thread\APM32F407\applications" -I"D:\Xhh_files\RT_Thread\APM32F407\board" -I"D:\Xhh_files\RT_Thread\APM32F407\libraries\APM32F4xx_Library\APM32F4xx_StdPeriphDriver\inc" -I"D:\Xhh_files\RT_Thread\APM32F407\libraries\APM32F4xx_Library\CMSIS\Include" -I"D:\Xhh_files\RT_Thread\APM32F407\libraries\APM32F4xx_Library\Device\Geehy\APM32F4xx\Include" -I"D:\Xhh_files\RT_Thread\APM32F407\libraries\Drivers" -I"D:\Xhh_files\RT_Thread\APM32F407\rt-thread\components\dfs\include" -I"D:\Xhh_files\RT_Thread\APM32F407\rt-thread\components\drivers\include" -I"D:\Xhh_files\RT_Thread\APM32F407\rt-thread\components\finsh" -I"D:\Xhh_files\RT_Thread\APM32F407\rt-thread\components\libc\compilers\common\include" -I"D:\Xhh_files\RT_Thread\APM32F407\rt-thread\components\libc\compilers\newlib" -I"D:\Xhh_files\RT_Thread\APM32F407\rt-thread\components\libc\posix\io\poll" -I"D:\Xhh_files\RT_Thread\APM32F407\rt-thread\components\libc\posix\io\stdio" -I"D:\Xhh_files\RT_Thread\APM32F407\rt-thread\components\libc\posix\ipc" -I"D:\Xhh_files\RT_Thread\APM32F407\rt-thread\include" -I"D:\Xhh_files\RT_Thread\APM32F407\rt-thread\libcpu\arm\common" -I"D:\Xhh_files\RT_Thread\APM32F407\rt-thread\libcpu\arm\cortex-m4" -include"D:\Xhh_files\RT_Thread\APM32F407\rtconfig_preinc.h" -std=gnu11 -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

