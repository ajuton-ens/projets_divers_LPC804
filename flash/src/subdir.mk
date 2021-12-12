################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/CB_RX0.c \
../src/CB_TX0.c \
../src/GPIO_hexapode.c \
../src/MCUXpresso_cr_startup.c \
../src/MCUXpresso_crp.c \
../src/MCUXpresso_mtb.c \
../src/MRT_hexapode.c \
../src/UART_hexapode.c \
../src/lib_ENS_II1_lcd.c \
../src/main.c \
../src/protocol.c \
../src/robotCommand.c \
../src/system.c \
../src/toolbox.c 

OBJS += \
./src/CB_RX0.o \
./src/CB_TX0.o \
./src/GPIO_hexapode.o \
./src/MCUXpresso_cr_startup.o \
./src/MCUXpresso_crp.o \
./src/MCUXpresso_mtb.o \
./src/MRT_hexapode.o \
./src/UART_hexapode.o \
./src/lib_ENS_II1_lcd.o \
./src/main.o \
./src/protocol.o \
./src/robotCommand.o \
./src/system.o \
./src/toolbox.o 

C_DEPS += \
./src/CB_RX0.d \
./src/CB_TX0.d \
./src/GPIO_hexapode.d \
./src/MCUXpresso_cr_startup.d \
./src/MCUXpresso_crp.d \
./src/MCUXpresso_mtb.d \
./src/MRT_hexapode.d \
./src/UART_hexapode.d \
./src/lib_ENS_II1_lcd.d \
./src/main.d \
./src/protocol.d \
./src/robotCommand.d \
./src/system.d \
./src/toolbox.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -DCR_INTEGER_PRINTF -D__USE_CMSIS -D__CODE_RED -DCORE_M0PLUS -D__MTB_DISABLE -D__MTB_BUFFER_SIZE=256 -D__REDLIB__ -I"C:\Users\Pierre-Alexandre\Desktop\Etudes\441 - Informatique industrielle\Code\TP_HEXAPODE\inc" -I"C:\Users\Pierre-Alexandre\Desktop\Etudes\441 - Informatique industrielle\Code\peripherals_lib\inc" -I"C:\Users\Pierre-Alexandre\Desktop\Etudes\441 - Informatique industrielle\Code\utilities_lib\inc" -I"C:\Users\Pierre-Alexandre\Desktop\Etudes\441 - Informatique industrielle\Code\common\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


