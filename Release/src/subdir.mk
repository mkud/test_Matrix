################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CMyMatrix.cpp \
../src/CMyVector.cpp \
../src/test_Matrix.cpp 

OBJS += \
./src/CMyMatrix.o \
./src/CMyVector.o \
./src/test_Matrix.o 

CPP_DEPS += \
./src/CMyMatrix.d \
./src/CMyVector.d \
./src/test_Matrix.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


