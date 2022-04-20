/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>
#include <modbus.h>
#include <registers.h>

void board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	
	WDT->WDT_MR |= WDT_MR_WDDIS; // Disable watchdog timer to prevent uC resetting every 15 seconds :)
	
	//Enable USB Comm port so we can send debug data over serial to a computer (could be useful)
	//Configuration for this is in conf_usb.h
	
	//udc_start();
	
	pmc_enable_periph_clk(ID_PIOA);
	pmc_enable_periph_clk(ID_PIOB);
	
	pio_set_output(RS485_NRE_PORT,RS485_NRE,LOW,DISABLE,DISABLE);			//init modbus receive enable pin		//only necessary for low power mode builds
	modbus_init(UART1,500000,RS485_DE_PORT,RS485_DE,SLAVEID);					//init modbus      //note this version of modbus has been modified to support sleep mode
	
	NVIC_EnableIRQ(PIOA_IRQn);
	pio_set_output(TEMP_SEL0_PORT,TEMP_SEL0,LOW,DISABLE,DISABLE);
	pio_set_output(TEMP_SEL1_PORT,TEMP_SEL1,LOW,DISABLE,DISABLE);
	pio_set_output(TEMP_SEL2_PORT,TEMP_SEL2,LOW,DISABLE,DISABLE);
	
	pio_set_output(CELL_SEL0_PORT,CELL_SEL0,LOW,DISABLE,DISABLE);
	pio_set_output(CELL_SEL1_PORT,CELL_SEL0,LOW,DISABLE,DISABLE);
	pio_set_output(CELL_SEL2_PORT,CELL_SEL0,LOW,DISABLE,DISABLE);
	
	pio_set_output(AFE_EN_PORT,AFE_EN,HIGH,DISABLE,DISABLE);
	
	pio_set_output(NBAT_EN_PORT,NBAT_EN,HIGH,DISABLE,DISABLE);
	
	pio_set_output(BOARD_LED_PORT,BOARD_LED,HIGH,DISABLE,DISABLE);
	
	pio_set_input(PWR_SW_PORT,PWR_SW,PIO_DEBOUNCE);
	
	pio_set_input(USB_SNS_PORT,USB_SNS,PIO_DEBOUNCE);
	
	pio_set_input(CELLV_SNS_PORT,CELLV_SNS,NULL);
	
	pio_set_input(CURRENT_SNS_PORT,CURRENT_SNS,NULL);
	
	pio_set_input(STACK_SNS_PORT,STACK_SNS,NULL);
	
	pio_set_input(EXT_TEMP_SNS_PORT,EXT_TEMP_SNS,NULL);
	
	pio_set_input(FETTEMP_SNS_PORT,FETTEMP_SNS,NULL);
	
	pio_set_input(SHUNTTEMP_SNS_PORT,SHUNTTEMP_SNS,NULL);
	
	pio_enable_pin_interrupt(0);
	pio_enable_pin_interrupt(14);
	
}