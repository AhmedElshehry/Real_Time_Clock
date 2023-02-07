################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_Program.c \
../KPD_program.c \
../LCD_Program.c \
../Sevenseg_Program.c \
../gi_program.c \
../mian.c \
../timer_program.c 

OBJS += \
./DIO_Program.o \
./KPD_program.o \
./LCD_Program.o \
./Sevenseg_Program.o \
./gi_program.o \
./mian.o \
./timer_program.o 

C_DEPS += \
./DIO_Program.d \
./KPD_program.d \
./LCD_Program.d \
./Sevenseg_Program.d \
./gi_program.d \
./mian.d \
./timer_program.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


