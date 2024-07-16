# Pac-Man using an STM32F401RE

### Terminologies
- DDRAM: Display Data RAM which stores the character to be shown at particular positions. Since I am using a 16x2 display, 32 characters can be shown.

## Materials
1. 2004 I2C LCD (Character Display Module LCD - Color I2C 99.00mm x 60.00mm x 22.00mm)
2. ANALOG 2-AXIS THUMB JOYSTICK WIT
3. BUZZER PIEZO 3V 12.2MM TH
4. BREADBRD TERM STRIP 3.20X2.00"
5. Wires to connect

![image](https://github.com/user-attachments/assets/d3690178-f210-460b-88df-5f05370047e6)

## Connections
- The LCD has four connections: GND, VCC, SDA, and SCL
  - In STM32CubeMX, PB9 is set to I2C1_SDA (SDA/D14) and PB8 (SCL/D15) is set to I2C_SCL
  - ![image](https://github.com/user-attachments/assets/88de7ac6-46ff-428b-a5d1-e7ca8b57d041)
- The joystick has 5 connections: GND, VCC, SEL, XOUT, and YOUT
  - SEL is set as GPIO_Input on PA10 (D2)
  - XOUT is set as ADC1_IN11 on PC1 (A4)
  - YOUT is set as ADC1_IN10 on PC0 (A5)
- The buzzer is set as GPIO_Input on PB10 (PWM/D6)

![image2](https://github.com/user-attachments/assets/51b45d16-cd63-412f-bfd8-c203b666af73)
![image](https://github.com/user-attachments/assets/5a4ca3f4-88b6-4894-b530-74c42caa9e5e)

## LCD with PCF8574
The PCF8574 expansion allows for easier setup of the data transfer between the display and the microcontroller board. The display itself has the following pins: VSS, VDD, V0, RS (0 for command and 1 for data), R/W, E (enable signal), D0 - D7 pins, A, and K.

The most important pins are the RS, R/W and the E signals as they depend on the instruction being sent to or from the display. If the bits are an instruction, RS is 0. E should be 1 when the data is being sent and must be set to 1 after data transfer to notify of the end of transfer.

To use the I2C protocol, a [LCD I2C library](https://controllerstech.com/i2c-lcd-in-stm32/) was imported to the project. The three functions that I have referred to are: lcd_send_cmd, lcd_send_data, and lcd_init. The rest of the functions were written by me using the data sheet.

### Library Functions
- clear_display (void)
  - This clears the display data, resets the address counter, and returns the cursor to the top left of the display.
- return_home (void)
  - Move the cursor to the top left of the display.
- entry_mode (int dir, int s)
  - Cursor direction
  - I/D: Increment (move the cursor to right) or decrement (move the cursor to left) the address of DDRAM
  - S: Shift the display left or right
- display_on_off (int d, int c, int b)
  - Turn the display on or off (data is not lost)
  - No cursor displayed (just a visual thing)
  - Cursor blink
- function_set (int dl, int n int f)
  - 8-bit or 4 bit
  - 0 for 1 display line and 1 for 2 display lines
  - Font style 5x8 or 5x11
- 
