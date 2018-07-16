################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
src/PDI_displays_drivers/EPD_interface.obj: I:/PDI/Kit/EPD\ Extension\ Board\ GEN2/fw/V1_21/EPD\ Extension\ Board\ Gen2\ (EXT2)_v1.21\ formal/EPD_drivers/src/EPD_interface.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me -Ooff --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/CC3200SDK_1.3.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.3.0/cc3200-sdk/driverlib" --include_path="C:/ti/CC3200SDK_1.3.0/cc3200-sdk/inc" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/CC3200 LaunchPad/src" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/CC3200 LaunchPad/src/HW_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/CC3200 LaunchPad/src/PDI_displays_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/EPD_drivers/src/FPL_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/EPD_drivers/src" --define=ccs --define=NON_NETWORK --define=cc3200 --define=iTC_215_Aurora_Mb --define=USE_EPD_Type=dr_iTC_BWb --define=USE_EPD_Size=sz_iTC_215 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="src/PDI_displays_drivers/EPD_interface.d_raw" --obj_directory="src/PDI_displays_drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/PDI_displays_drivers/iTC_215_Mb_LUT.obj: ../src/PDI_displays_drivers/iTC_215_Mb_LUT.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me -Ooff --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/CC3200SDK_1.3.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.3.0/cc3200-sdk/driverlib" --include_path="C:/ti/CC3200SDK_1.3.0/cc3200-sdk/inc" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/CC3200 LaunchPad/src" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/CC3200 LaunchPad/src/HW_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/CC3200 LaunchPad/src/PDI_displays_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/EPD_drivers/src/FPL_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/EPD_drivers/src" --define=ccs --define=NON_NETWORK --define=cc3200 --define=iTC_215_Aurora_Mb --define=USE_EPD_Type=dr_iTC_BWb --define=USE_EPD_Size=sz_iTC_215 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="src/PDI_displays_drivers/iTC_215_Mb_LUT.d_raw" --obj_directory="src/PDI_displays_drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


