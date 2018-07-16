################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
msp432_startup_ccs.obj: ../msp432_startup_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --opt_for_speed=2 --fp_mode=relaxed --include_path="C:/ti/ccsv7/ccs_base/arm/include" --include_path="C:/ti/msp/MSP432Ware_3_50_00_02/driverlib/driverlib/MSP432P4xx" --include_path="C:/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/ti/ccsv7/ccs_base/arm/include/" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include/" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/MSP-Exp432P401R/src" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/MSP-Exp432P401R/src/HW_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/MSP-Exp432P401R/src/PDI_displays_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/EPD_drivers/src/FPL_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/EPD_drivers/src" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/PDI_apps_drivers" --advice:power="all" --define=__MSP432P401R__ --define=USE_PDI_APPs --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="msp432_startup_ccs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


