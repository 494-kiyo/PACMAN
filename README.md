# Pac-Man on Nucleo: Embedded Gaming with STM32
**DMA ADC, I2C LCD, Timer, Interrupts, and PWM**

![](https://github.com/esther494/PACMAN/blob/main/IMG_3559.gif)

This is an embedded project that recreates the most popular arcade game, Pac-Man, using an STM32F401RE Nucleo board and hardware peripherals. Features of this game inlcude:

- Multiple Levels: After completing a stage, the next one becomes increasingly difficult, as the speed of the AI enemy (the ghost) increases.
- AI Enemy: The enemy follows the player, updating its position based on a dedicated timer.
- Random Foods: All foods must be collected to advance to the next stage, and this must be done before being caught by the enemy.

## Hardware Integration
- I2C LCD [(2004 LCD)](https://www.digikey.ca/en/products/detail/sunfounder/CN0296D/18668625?utm_adgroup=&utm_term=&utm_content=&gad_source=1)
- Joystick [(Analog 2-axis Thumb Joystick with Select Button + Breakout Board)](https://www.digikey.ca/en/products/detail/adafruit-industries-llc/512/7056915)
- Buzzer [(PS1240P02BT)](https://www.digikey.ca/en/products/detail/tdk-corporation/PS1240P02BT/935924)

## Project Setup
![pinout](https://github.com/user-attachments/assets/7e0772ab-b280-4208-bb0f-35097a52222a) ![image](https://github.com/user-attachments/assets/d3690178-f210-460b-88df-5f05370047e6)

Hardware Connections:

- Display: PB9 is set to I2C1_SDA (SDA/D14) and PB8 (SCL/D15) is set to I2C_SCL
- JoyStick: SEL is set as GPIO_Input on PA10 (D2), XOUT is set as ADC1_IN11 on PC1 (A4), and YOUT is set as ADC1_IN10 on PC0 (A5)
- Buzzer: Set as GPIO_Input on PB10 (PWM/D6)

![clock](https://github.com/user-attachments/assets/85349fe5-90f4-4aee-86a8-f68934d45834)

### Display
To communicate with the display, I created a simple [library](pacman/Core/Src/i2c-lcd.c) which uses I2C. Two main functions are lcd_send_cmd and lcd_send_data which are used to communiate with the display. The En and Rs signals are used to let the display know if the content is a command or data and when to latch the data. Utility functions such as lcd_cursor_pos and lcd_send_string are used to change the cursor position on the display and send a series of characters at once, respectively. I also included functions to edit display configurations like flickering cursor.

### Joystick
To move the player using the joystick, it was important to make sure that the directions were being recognized real time, so a DMA was used with the ADC. Since this project was simple, I created a function that gets called after every main loop to reflect the change in direction, but it is more approperiate to use the callback function for ADC DMA to make it more real time.

![image](https://github.com/user-attachments/assets/6d782e9a-82e4-4390-bf4a-52add441d3d3)

In the current version of the project, I used four buttons to move the player instead of the joystick. This was because I accidentally broke my joystick and it was no longer recognizing the inputs. Since I could not use DMA anymore, I used interrupts to change the directions. 

### Buzzer
Timer is setup to generate frequencies for PWM signals. In this project, sounds were used to indicate the start of the game and the end of the game. To change the frequency of the sound, the prescaler of the timer was modified.

### Game Logic
