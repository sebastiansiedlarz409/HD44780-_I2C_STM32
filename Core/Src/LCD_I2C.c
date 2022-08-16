#include <LCD_I2C.h>
#include <stdint.h>

//INSERT MCU STDLIB HERE
#include "stm32l4xx_hal.h"

HAL_StatusTypeDef LCD_Begin(I2C_HandleTypeDef* hi2c, uint8_t address, uint8_t rows, uint8_t columns, uint8_t blink, uint8_t backlight){
	HAL_StatusTypeDef status = HAL_OK;

	lcd_hi2c = hi2c;
	lcd_address = address<<1;
	lcd_rows = rows;
	lcd_columns = columns;
	lcd_data = 0x00;

	LCD_BackLight(backlight);
	LCD_SendCmd(0);

	//init screen
	if(rows == 2){
		status |= LCD_SendCmd(0x28); //4bits 2 rows
	}
	else if(rows == 1){
		status |= LCD_SendCmd(0x20); //4bits 1 row
	}
	else{
		return HAL_ERROR;
	}

	//move to first position in first row
	if(blink){
		status |= LCD_SendCmd(TURNON_BLINK);
	}
	else{
		status |= LCD_SendCmd(TURNON_NOBLINK);
	}
	//status |= LCD_SendCmd(FIRST_ROW_START);

	status |= LCD_SendCmd(0x01);
	status |= LCD_SendCmd(0x02);

	return status;
}

HAL_StatusTypeDef LCD_Write(){
	return HAL_I2C_Master_Transmit(lcd_hi2c, lcd_address, &lcd_data, 1, 100);
}

HAL_StatusTypeDef LCD_SetPin(uint8_t pin, uint8_t state){
	if(pin>7) return HAL_ERROR;

	if(state > 0)
		lcd_data |= (1<<pin);
	else
		lcd_data &= ~(1<<pin);

	return HAL_OK;
}

HAL_StatusTypeDef LCD_BackLight(uint8_t on){
	if(on){
		return LCD_SetPin(BL, 1);
	}
	else{
		return LCD_SetPin(BL, 0);
	}
}

HAL_StatusTypeDef LCD_PulseEnable(){
	HAL_StatusTypeDef status = HAL_OK;

	status |= LCD_SetPin(EN, EN_ENABLE);
	status |= LCD_Write();
	HAL_Delay(10);
	status |= LCD_SetPin(EN, EN_DISABLE);
	status |= LCD_Write();
	HAL_Delay(10);

	return status;
}

HAL_StatusTypeDef LCD_SendCmd(uint8_t cmd){
	HAL_StatusTypeDef status = HAL_OK;

	uint8_t hn = (cmd>>4)&0x0F;
	uint8_t ln = cmd&0x0F;

	status |= LCD_SetPin(RW, RW_WRITE);
	status |= LCD_SetPin(RS, RS_CMD);

	lcd_data &= 0x0F; //clear data bits
	status |= LCD_SetPin(D4, hn&0b0001);
	status |= LCD_SetPin(D5, hn&0b0010);
	status |= LCD_SetPin(D6, hn&0b0100);
	status |= LCD_SetPin(D7, hn&0b1000);
	status |= LCD_PulseEnable();

	lcd_data &= 0x0F; //clear data bits
	status |= LCD_SetPin(D4, ln&0b0001);
	status |= LCD_SetPin(D5, ln&0b0010);
	status |= LCD_SetPin(D6, ln&0b0100);
	status |= LCD_SetPin(D7, ln&0b1000);
	status |= LCD_PulseEnable();

	return status;
}

HAL_StatusTypeDef LCD_SendData(uint8_t data){
	HAL_StatusTypeDef status = HAL_OK;

	uint8_t hn = (data>>4)&0x0F;
	uint8_t ln = data&0x0F;

	status |= LCD_SetPin(RW, RW_WRITE);
	status |= LCD_SetPin(RS, RS_DATA);

	lcd_data &= 0x0F; //clear data bits
	status |= LCD_SetPin(D4, hn&0b0001);
	status |= LCD_SetPin(D5, hn&0b0010);
	status |= LCD_SetPin(D6, hn&0b0100);
	status |= LCD_SetPin(D7, hn&0b1000);
	status |= LCD_PulseEnable();

	lcd_data &= 0x0F; //clear data bits
	status |= LCD_SetPin(D4, ln&0b0001);
	status |= LCD_SetPin(D5, ln&0b0010);
	status |= LCD_SetPin(D6, ln&0b0100);
	status |= LCD_SetPin(D7, ln&0b1000);
	status |= LCD_PulseEnable();

	return status;
}

HAL_StatusTypeDef LCD_SendCharacter(uint8_t chr){
	return LCD_SendData(chr);
}

HAL_StatusTypeDef LCD_SendString(const char* str){
	HAL_StatusTypeDef status = HAL_OK;
	while(*str){
		status |= LCD_SendCharacter((uint8_t)*str);
		str++;
	}
	return status;
}
