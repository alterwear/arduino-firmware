################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
tm4c123gh6pm_startup_ccs.obj: ../tm4c123gh6pm_startup_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --opt_for_speed=0 --fp_mode=relaxed --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/EK-TM4C123GXL/src" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/EK-TM4C123GXL/src/HW_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/EK-TM4C123GXL/src/PDI_displays_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/EPD_drivers/src/FPL_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/EPD_drivers/src" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/EK-TM4C123GXL/driverlib" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/PDI_apps_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/EPD_drivers/src/FPL_drivers" --define=ccs="ccs" --define=TARGET_IS_TM4C123_RB1 --define=PART_TM4C123GH6PM --define=USE_PDI_APPs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --small_enum --preproc_with_compile --preproc_dependency="tm4c123gh6pm_startup_ccs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


