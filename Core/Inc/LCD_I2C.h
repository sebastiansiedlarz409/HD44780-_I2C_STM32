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

I2C_HandleTypeDef* lcd_hi2c;
uint8_t lcd_address;
uint8_t lcd_rows;
uint8_t lcd_columns;
uint8_t lcd_data;

HAL_StatusTypeDef LCD_Begin(I2C_HandleTypeDef* hi2c, uint8_t address, uint8_t rows, uint8_t columns);
HAL_StatusTypeDef LCD_Write();
HAL_StatusTypeDef LCD_SetPin(uint8_t pin, uint8_t state);
