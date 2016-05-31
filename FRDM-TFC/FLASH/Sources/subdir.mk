################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/LEDs.c" \
"../Sources/LineScanCam.c" \
"../Sources/config.c" \
"../Sources/main.c" \
"../Sources/motorServo.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/LEDs.c \
../Sources/LineScanCam.c \
../Sources/config.c \
../Sources/main.c \
../Sources/motorServo.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/LEDs.o \
./Sources/LineScanCam.o \
./Sources/config.o \
./Sources/main.o \
./Sources/motorServo.o \
./Sources/sa_mtb.o \

C_DEPS += \
./Sources/LEDs.d \
./Sources/LineScanCam.d \
./Sources/config.d \
./Sources/main.d \
./Sources/motorServo.d \
./Sources/sa_mtb.d \

OBJS_QUOTED += \
"./Sources/LEDs.o" \
"./Sources/LineScanCam.o" \
"./Sources/config.o" \
"./Sources/main.o" \
"./Sources/motorServo.o" \
"./Sources/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/LEDs.d" \
"./Sources/LineScanCam.d" \
"./Sources/config.d" \
"./Sources/main.d" \
"./Sources/motorServo.d" \
"./Sources/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/LEDs.o \
./Sources/LineScanCam.o \
./Sources/config.o \
./Sources/main.o \
./Sources/motorServo.o \
./Sources/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/LEDs.o: ../Sources/LEDs.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/LEDs.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/LEDs.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/LineScanCam.o: ../Sources/LineScanCam.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/LineScanCam.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/LineScanCam.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/config.o: ../Sources/config.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/config.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/config.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/motorServo.o: ../Sources/motorServo.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/motorServo.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/motorServo.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


