################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
src/HW_drivers/Board_HW_Driver.obj: ../src/HW_drivers/Board_HW_Driver.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_17.9.0.STS/bin/cl430" -vmspx --data_model=restricted -O0 --opt_for_speed=1 --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_17.9.0.STS/include" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/MSP-Exp430F5529LP/driverlib/MSP430F5xx_6xx" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/MSP-Exp430F5529LP/src" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/MSP-Exp430F5529LP/src/HW_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/MSP-Exp430F5529LP/src/PDI_displays_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/EPD_drivers/src/FPL_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/EPD_drivers/src" --define=__MSP430F5529__ --define=DEPRECATED --define=eTC_G2_Aurora_Mb --define=USE_EPD_Type=dr_eTC_BWb --define=USE_EPD_Size=sz_eTC_200 -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --small_enum --preproc_with_compile --preproc_dependency="src/HW_drivers/Board_HW_Driver.d_raw" --obj_directory="src/HW_drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/HW_drivers/EPD_Temperature_IIC.obj: ../src/HW_drivers/EPD_Temperature_IIC.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_17.9.0.STS/bin/cl430" -vmspx --data_model=restricted -O0 --opt_for_speed=1 --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_17.9.0.STS/include" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/MSP-Exp430F5529LP/driverlib/MSP430F5xx_6xx" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/MSP-Exp430F5529LP/src" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/MSP-Exp430F5529LP/src/HW_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/MSP-Exp430F5529LP/src/PDI_displays_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/EPD_drivers/src/FPL_drivers" --include_path="I:/PDI/Kit/EPD Extension Board GEN2/fw/V1_21/EPD Extension Board Gen2 (EXT2)_v1.21 formal/EPD_drivers/src" --define=__MSP430F5529__ --define=DEPRECATED --define=eTC_G2_Aurora_Mb --define=USE_EPD_Type=dr_eTC_BWb --define=USE_EPD_Size=sz_eTC_200 -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --small_enum --preproc_with_compile --preproc_dependency="src/HW_drivers/EPD_Temperature_IIC.d_raw" --obj_directory="src/HW_drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


