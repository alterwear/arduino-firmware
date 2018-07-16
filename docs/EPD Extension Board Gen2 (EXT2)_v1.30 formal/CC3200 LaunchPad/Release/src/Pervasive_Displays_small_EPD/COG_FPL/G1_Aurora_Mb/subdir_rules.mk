################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/Pervasive_Displays_small_EPD/COG_FPL/G1_Aurora_Mb/EPD_G1_Aurora_Mb.obj: ../src/Pervasive_Displays_small_EPD/COG_FPL/G1_Aurora_Mb/EPD_G1_Aurora_Mb.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/bin/armcl" -mv7M4 --code_state=16 --float_support=fpalib --abi=eabi -me -Ooff --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/include" --include_path="C:/ti/CC3200SDK_1.1.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.1.0/cc3200-sdk/driverlib" --include_path="C:/ti/CC3200SDK_1.1.0/cc3200-sdk/inc" --include_path="F:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/CC3200 LaunchPad/src" --include_path="F:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/CC3200 LaunchPad/src/Pervasive_Displays_small_EPD" -g --gcc --define=ccs --define=NON_NETWORK --define=cc3200 --diag_wrap=off --display_error_number --diag_warning=225 --preproc_with_compile --preproc_dependency="src/Pervasive_Displays_small_EPD/COG_FPL/G1_Aurora_Mb/EPD_G1_Aurora_Mb.pp" --obj_directory="src/Pervasive_Displays_small_EPD/COG_FPL/G1_Aurora_Mb" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


