#create:2018-10-12
#auther:zsl,wb

#方便阅读本文件的知识
#(1)字符'\'表示换行
#(2)所有目标的第一条指令前必须有一个tab，不可用4个空格代替
#(3)$@  表示目标文件
#   $^  表示所有的依赖文件
#   $<  表示第一个依赖文件
#   $?  表示比目标还要新的依赖文件列表

#定义本文件中使用到的变量【根据实际需要修改】
#控制台输出程序路径
printf    := echo

#.C文件文件夹
SRC_C := ./srcc
#.S文件文件夹
SRC_S := ./srcs
#.o文件存放目录
D_OBJ := ./obj
#.d文件存放目录
D_MK  := ./dmk
#.C文件列表
SRC_CList := $(wildcard ./srcc/*.c)
SRC_CPPList := $(wildcard ./srcc/*.cpp)
#.S文件列表
SRC_SList := $(wildcard ./srcs/*.S)

#链接文件(.ld)的存储路径
linkFile := "E:\KL36\KL36_Demo_1\03_MCU\linker_file\MKL36Z64xxx4_flash.ld"
#定义生成的文件名
finalGoal := KL36_Demo_1
#定义头文件所在的路径
include := -I"E:\KL36\KL36_Demo_1\.settings" -I"E:\KL36\KL36_Demo_1\01_Doc" -I"E:\KL36\KL36_Demo_1\02_CPU" -I"E:\KL36\KL36_Demo_1\03_MCU" -I"E:\KL36\KL36_Demo_1\04_GEC" -I"E:\KL36\KL36_Demo_1\05_UserBoard" -I"E:\KL36\KL36_Demo_1\06_SoftComponent" -I"E:\KL36\KL36_Demo_1\07_NosPrg" -I"E:\KL36\KL36_Demo_1\Debug" -I"E:\KL36\KL36_Demo_1\03_MCU\linker_file" -I"E:\KL36\KL36_Demo_1\03_MCU\MCU_drivers" -I"E:\KL36\KL36_Demo_1\03_MCU\startup" -I"E:\KL36\KL36_Demo_1\Debug\obj" -I"E:\KL36\KL36_Demo_1\Debug\srcc" -I"E:\KL36\KL36_Demo_1\Debug\srcs"
#定义优化级别。共有O0、O1、O2、Os和Og，默认使用Og
opt := Og
#.o文件列表
OBJ_C := $(addprefix $(D_OBJ)/,$(patsubst %.c,%.o,$(notdir $(SRC_CList))))
OBJ_C += $(addprefix $(D_OBJ)/,$(patsubst %.cpp,%.o,$(notdir $(SRC_CPPList))))
OBJ_C += $(addprefix $(D_OBJ)/,$(patsubst %.S,%.o,$(notdir $(SRC_SList))))
#.d文件列表
SRC_MK := $(addprefix $(D_OBJ)/, $(patsubst %.c,%.d,$(notdir $(SRC_CList))))
SRC_MK += $(addprefix $(D_OBJ)/, $(patsubst %.cpp,%.d,$(notdir $(SRC_CPPList))))
SRC_MK += $(addprefix $(D_OBJ)/, $(patsubst %.S,%.d,$(notdir $(SRC_SList))))

#将文件夹./Source中的.c文件编译为.o文件
#【20200306 1/1】姜家乐&王浩波 修改.c编译规则
$(D_OBJ)/%.o:$(SRC_C)/%.c
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 \
-fsigned-char -ffunction-sections -fdata-sections -fomit-frame-pointer  -g3 \
-D__CMSIS_RTOS -D__MBED_CMSIS_RTOS_CM -D__CORTEX_M0PLUS -DARM_MATH_CM0PLUS \
-DTARGET_LIKE_MBED -DTARGET_Freescale -DTOOLCHAIN_object -DTARGET_KLXX \
-DTARGET_CORTEX_M -DTARGET_M0P -DTARGET_UVISOR_UNSUPPORTED -DTARGET_FF_ARDUINO \
-DTARGET_RELEASE -DTOOLCHAIN_GCC -DTARGET_LIKE_CORTEX_M0 -DTARGET_CORTEX \
-DTOOLCHAIN_GCC_ARM -D__MBED__=1 -DDEVICE_I2CSLAVE=1 -DDEVICE_PORTINOUT=1 \
-DMBED_BUILD_TIMESTAMP=1517210728.91 -DDEVICE_ANALOGOUT=1 -DDEVICE_PWMOUT=1 \
-DDEVICE_INTERRUPTIN=1 -DDEVICE_I2C=1 -DDEVICE_PORTOUT=1 \
-DDEVICE_STDIO_MESSAGES=1 -DDEVICE_PORTIN=1 -DDEVICE_SPI=1 -DDEVICE_SPISLAVE=1 \
-DDEVICE_ANALOGIN=1 -DDEVICE_SERIAL=1 -DDEVICE_SEMIHOST=1 -DDEVICE_SLEEP=1 \
-DTARGET_KL36Z $(include) -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"


#将文件夹./Source中的.cpp文件编译为.o文件
$(D_OBJ)/%.o:$(SRC_C)/%.cpp
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fomit-frame-pointer  \
-g3 -D__CMSIS_RTOS -D__MBED_CMSIS_RTOS_CM -D__CORTEX_M0PLUS -DARM_MATH_CM0PLUS \
-DTARGET_LIKE_MBED  -DTARGET_CORTEX_M -DTARGET_M0P -DTOOLCHAIN_GCC \
-DTARGET_LIKE_CORTEX_M0 -DTARGET_CORTEX -DTOOLCHAIN_GCC_ARM -D__MBED__=1 \
-DTARGET_KL36Z $(include) -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"

#将文件夹./Source中的.S文件编译为.o文件 
$(D_OBJ)/%.o:$(SRC_S)/%.S
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fomit-frame-pointer  \
-g3 -x assembler-with-cpp -D__CMSIS_RTOS -D__MBED_CMSIS_RTOS_CM -D__CORTEX_M0PLUS \
-DARM_MATH_CM0PLUS -DTARGET_LIKE_MBED -DTARGET_CORTEX_M -DTARGET_M0P \
-DTOOLCHAIN_GCC -DTARGET_LIKE_CORTEX_M0 -DTARGET_CORTEX -DTOOLCHAIN_GCC_ARM -D__MBED__=1 \
-DTARGET_KL36Z $(include) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"


# 罗列文件中的目标。目标为希望生成的文件。其中“all”和“clean”为伪目标
all:$(finalGoal).lst $(finalGoal).hex

$(finalGoal).elf: $(OBJ_C)
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 \
-fsigned-char -ffunction-sections -fdata-sections -fomit-frame-pointer  \
-g3 -T $(linkFile) -Xlinker --gc-sections -L$(linkFile) -Wl,-Map,"$(finalGoal).map" \
-specs=nano.specs -specs=nosys.specs -o "$(finalGoal).elf" $(OBJ_C)
	@$(printf) 'Finished building target: $@'
	@$(printf) ' '

$(finalGoal).hex: $(finalGoal).elf 
	arm-none-eabi-objcopy -O ihex "$<"  "$@"
	@$(printf) 'Finished building: $@'
	@$(printf) ' '
	
$(finalGoal).lst: $(finalGoal).elf
	arm-none-eabi-objdump --source --all-headers --demangle --line-numbers --wide "$(finalGoal).elf" > "$(finalGoal).lst"
	@$(printf) 'Finished building: $@'
	@$(printf) ' '

#设置清理工作空间的伪目标
#仅删除目标文件，其它文件若未发生变动则不编译，有利于提高编译速度
fastClean:
	rm -rf "$(finalGoal).elf" "$(finalGoal).hex" "$(finalGoal).map"
	-@$(printf) 'make: fast clean has be done'
	-@$(printf) ' '
#删除所有中间文件和目标文件，全部重新编译	
clean:
	rm -rf  "$(finalGoal).elf" "$(finalGoal).hex" "$(finalGoal).map" "$(finalGoal).hex" "$(finalGoal).lst" $(OBJ_C) $(SRC_MK)
	-@$(printf) 'make: clean has be done'
	-@$(printf) ' '
test:
	-@$(printf)  $(OBJ_C)
	
#指定哪些目标为伪目标
.PHONY: all clean fastClean test


