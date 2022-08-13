#pragma once

#include <stdint.h>

//INSERT MCU STDLIB HERE
#include "stm32l4xx_hal.h"

//SCREEN PINS
#define RS 0
#define RW 1
#define EN 2
#define BL 3 //backlight

#define D7 7
#define D6 6
#define D5 5
#define D4 4

#define RS_CMD 0
#define RS_DATA 1

#define RW_WRITE 0
#define RW_READ 1

#define EN_ENABLE 1
#define EN_DISABLE 0

//COMMANDS
#define TURNON_BLINK 		0x0F
#define TURNON_NOBLINK 		0x0E

#define FIRST_ROW_START 	0x80
#define SECOND_ROW_START	0xC0

I2C_HandleTypeDef* lcd_hi2c;
uint8_t lcd_address;
uint8_t lcd_rows;
uint8_t lcd_columns;
uint8_t lcd_data;

HAL_StatusTypeDef LCD_Begin(I2C_HandleTypeDef* hi2c, uint8_t address, uint8_t rows, uint8_t columns, uint8_t backlight);
HAL_StatusTypeDef LCD_Write();
HAL_StatusTypeDef LCD_ClearDataLine();
HAL_StatusTypeDef LCD_SetPin(uint8_t pin, uint8_t state);
HAL_StatusTypeDef LCD_SendCmd(uint8_t cmd);
HAL_StatusTypeDef LCD_BackLight(uint8_t on);
