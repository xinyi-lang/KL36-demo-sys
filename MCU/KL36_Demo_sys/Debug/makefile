#create:2018-10-12
#auther:zsl,wb

#�����Ķ����ļ���֪ʶ
#(1)�ַ�'\'��ʾ����
#(2)����Ŀ��ĵ�һ��ָ��ǰ������һ��tab��������4���ո����
#(3)$@  ��ʾĿ���ļ�
#   $^  ��ʾ���е������ļ�
#   $<  ��ʾ��һ�������ļ�
#   $?  ��ʾ��Ŀ�껹Ҫ�µ������ļ��б�

#���屾�ļ���ʹ�õ��ı���������ʵ����Ҫ�޸ġ�
#����̨�������·��
printf    := echo

#.C�ļ��ļ���
SRC_C := ./srcc
#.S�ļ��ļ���
SRC_S := ./srcs
#.o�ļ����Ŀ¼
D_OBJ := ./obj
#.d�ļ����Ŀ¼
D_MK  := ./dmk
#.C�ļ��б�
SRC_CList := $(wildcard ./srcc/*.c)
SRC_CPPList := $(wildcard ./srcc/*.cpp)
#.S�ļ��б�
SRC_SList := $(wildcard ./srcs/*.S)

#�����ļ�(.ld)�Ĵ洢·��
linkFile := "E:\KL36\KL36_Demo_1\03_MCU\linker_file\MKL36Z64xxx4_flash.ld"
#�������ɵ��ļ���
finalGoal := KL36_Demo_1
#����ͷ�ļ����ڵ�·��
include := -I"E:\KL36\KL36_Demo_1\.settings" -I"E:\KL36\KL36_Demo_1\01_Doc" -I"E:\KL36\KL36_Demo_1\02_CPU" -I"E:\KL36\KL36_Demo_1\03_MCU" -I"E:\KL36\KL36_Demo_1\04_GEC" -I"E:\KL36\KL36_Demo_1\05_UserBoard" -I"E:\KL36\KL36_Demo_1\06_SoftComponent" -I"E:\KL36\KL36_Demo_1\07_NosPrg" -I"E:\KL36\KL36_Demo_1\Debug" -I"E:\KL36\KL36_Demo_1\03_MCU\linker_file" -I"E:\KL36\KL36_Demo_1\03_MCU\MCU_drivers" -I"E:\KL36\KL36_Demo_1\03_MCU\startup" -I"E:\KL36\KL36_Demo_1\Debug\obj" -I"E:\KL36\KL36_Demo_1\Debug\srcc" -I"E:\KL36\KL36_Demo_1\Debug\srcs"
#�����Ż����𡣹���O0��O1��O2��Os��Og��Ĭ��ʹ��Og
opt := Og
#.o�ļ��б�
OBJ_C := $(addprefix $(D_OBJ)/,$(patsubst %.c,%.o,$(notdir $(SRC_CList))))
OBJ_C += $(addprefix $(D_OBJ)/,$(patsubst %.cpp,%.o,$(notdir $(SRC_CPPList))))
OBJ_C += $(addprefix $(D_OBJ)/,$(patsubst %.S,%.o,$(notdir $(SRC_SList))))
#.d�ļ��б�
SRC_MK := $(addprefix $(D_OBJ)/, $(patsubst %.c,%.d,$(notdir $(SRC_CList))))
SRC_MK += $(addprefix $(D_OBJ)/, $(patsubst %.cpp,%.d,$(notdir $(SRC_CPPList))))
SRC_MK += $(addprefix $(D_OBJ)/, $(patsubst %.S,%.d,$(notdir $(SRC_SList))))

#���ļ���./Source�е�.c�ļ�����Ϊ.o�ļ�
#��20200306 1/1��������&���Ʋ� �޸�.c�������
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


#���ļ���./Source�е�.cpp�ļ�����Ϊ.o�ļ�
$(D_OBJ)/%.o:$(SRC_C)/%.cpp
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fomit-frame-pointer  \
-g3 -D__CMSIS_RTOS -D__MBED_CMSIS_RTOS_CM -D__CORTEX_M0PLUS -DARM_MATH_CM0PLUS \
-DTARGET_LIKE_MBED  -DTARGET_CORTEX_M -DTARGET_M0P -DTOOLCHAIN_GCC \
-DTARGET_LIKE_CORTEX_M0 -DTARGET_CORTEX -DTOOLCHAIN_GCC_ARM -D__MBED__=1 \
-DTARGET_KL36Z $(include) -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"

#���ļ���./Source�е�.S�ļ�����Ϊ.o�ļ� 
$(D_OBJ)/%.o:$(SRC_S)/%.S
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fomit-frame-pointer  \
-g3 -x assembler-with-cpp -D__CMSIS_RTOS -D__MBED_CMSIS_RTOS_CM -D__CORTEX_M0PLUS \
-DARM_MATH_CM0PLUS -DTARGET_LIKE_MBED -DTARGET_CORTEX_M -DTARGET_M0P \
-DTOOLCHAIN_GCC -DTARGET_LIKE_CORTEX_M0 -DTARGET_CORTEX -DTOOLCHAIN_GCC_ARM -D__MBED__=1 \
-DTARGET_KL36Z $(include) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"


# �����ļ��е�Ŀ�ꡣĿ��Ϊϣ�����ɵ��ļ������С�all���͡�clean��ΪαĿ��
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

#�������������ռ��αĿ��
#��ɾ��Ŀ���ļ��������ļ���δ�����䶯�򲻱��룬��������߱����ٶ�
fastClean:
	rm -rf "$(finalGoal).elf" "$(finalGoal).hex" "$(finalGoal).map"
	-@$(printf) 'make: fast clean has be done'
	-@$(printf) ' '
#ɾ�������м��ļ���Ŀ���ļ���ȫ�����±���	
clean:
	rm -rf  "$(finalGoal).elf" "$(finalGoal).hex" "$(finalGoal).map" "$(finalGoal).hex" "$(finalGoal).lst" $(OBJ_C) $(SRC_MK)
	-@$(printf) 'make: clean has be done'
	-@$(printf) ' '
test:
	-@$(printf)  $(OBJ_C)
	
#ָ����ЩĿ��ΪαĿ��
.PHONY: all clean fastClean test

