#include <LCD_I2C.h>
#include <stdint.h>

//INSERT MCU STDLIB HERE
#include "stm32l4xx_hal.h"

HAL_StatusTypeDef LCD_Begin(I2C_HandleTypeDef* hi2c, uint8_t address, uint8_t rows, uint8_t columns){
	HAL_StatusTypeDef status = HAL_OK;

	lcd_hi2c = hi2c;
	lcd_address = address<<1;
	lcd_rows = rows;
	lcd_columns = columns;
	lcd_data = 0x00;

	return status;
}

HAL_StatusTypeDef LCD_Write(){
	return HAL_I2C_Master_Transmit(lcd_hi2c, lcd_address, &lcd_data, 1, 100);
}

HAL_StatusTypeDef LCD_SetPin(uint8_t pin, uint8_t state){
	if(pin>7) return HAL_ERROR;

	if(state == 1)
		lcd_data |= (1<<pin);
	else if(state == 0)
		lcd_data &= ~(1<<pin);
	else
		return HAL_ERROR;

	return HAL_OK;
}
