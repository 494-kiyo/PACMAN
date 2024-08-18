# Pac-Man on Nucleo: Embedded Gaming with STM32
**DMA ADC, I2C LCD, Timer, Interrupts, and PWM**

![](https://github.com/esther494/PACMAN/blob/main/IMG_3559.gif)

This is an embedded project that recreates the popular arcade game Pac-Man using an STM32F401RE Nucleo board and hardware peripherals. Features of this game include:

- **Multiple Levels:** After completing a stage, the next one becomes increasingly difficult as the speed of the AI enemy (the ghost) increases.
- **AI Enemy:** The enemy follows the player, updating its position based on a dedicated timer.
- **Random Foods:** All foods must be collected to advance to the next stage, and this must be done before being caught by the enemy.

## Hardware Integration
- I2C LCD [(2004 LCD)](https://www.digikey.ca/en/products/detail/sunfounder/CN0296D/18668625?utm_adgroup=&utm_term=&utm_content=&gad_source=1)
- Joystick [(Analog 2-axis Thumb Joystick with Select Button + Breakout Board)](https://www.digikey.ca/en/products/detail/adafruit-industries-llc/512/7056915)
- Buzzer [(PS1240P02BT)](https://www.digikey.ca/en/products/detail/tdk-corporation/PS1240P02BT/935924)

## Project Setup
![pinout](https://github.com/user-attachments/assets/7e0772ab-b280-4208-bb0f-35097a52222a) ![image](https://github.com/user-attachments/assets/d3690178-f210-460b-88df-5f05370047e6)

Hardware Connections:

- **Display:** PB9 is set to I2C1_SDA (SDA/D14) and PB8 (SCL/D15) is set to I2C_SCL.
- **Joystick:** SEL is set as GPIO_Input on PA10 (D2), XOUT is set as ADC1_IN11 on PC1 (A4), and YOUT is set as ADC1_IN10 on PC0 (A5).
- **Buzzer:** Set as GPIO_Output on PB10 (PWM/D6).

![clock](https://github.com/user-attachments/assets/85349fe5-90f4-4aee-86a8-f68934d45834)

### Display
To communicate with the display, I created a simple [library](pacman/Core/Src/i2c-lcd.c) that uses I2C. Two main functions, lcd_send_cmd and lcd_send_data, are used to communicate with the display. The En and Rs signals indicate whether the content is a command or data and control when to latch the data. Utility functions such as lcd_cursor_pos and lcd_send_string are used to change the cursor position on the display and send a series of characters at once, respectively. I also included functions to modify display configurations, such as the flickering cursor.

### Joystick
To move the player using the joystick, it was important to ensure that the directions were recognized in real-time, so DMA was used with the ADC. Since this project was simple, I created a function that gets called after every main loop iteration to reflect the change in direction. However, it would be more appropriate to use the callback function for ADC DMA to make it more real-time.

![image](https://github.com/user-attachments/assets/6d782e9a-82e4-4390-bf4a-52add441d3d3)

In the current version of the project, I used four buttons to move the player instead of the joystick. This was due to a malfunction with the joystick, which was no longer recognizing inputs. Since I could not use DMA anymore, I used interrupts to change the directions. Another important consideration was to debounce the buttons, ensuring that a new input was received only after a certain period of time since the last input.

### Buzzer
The timer is set up to generate frequencies for PWM signals. In this project, sounds are used to indicate the start and end of the game. To change the frequency of the sound, the timer’s prescaler was modified.

## Game Logic
The functions for the game can be found [here](pacman/Core/Src/pacman.c). The game initialization sets the player’s and enemy’s positions, randomly generates and places food locations in a two-dimensional array, and saves the number of foods in the player’s class. The enemy moves automatically each time the timer autoreloads and is programmed to follow the player’s position by checking its row and column. To ensure the enemy moves only once per timer pulse, it tracks the previous timer pulse. The player’s moves are checked to prevent going out of bounds; if the player does go out of bounds, they are reset to the previous position. The game display function is called whenever the display needs to update, which occurs when either the player or enemy moves. The function first clears the display before printing the food, player, and enemy. Lastly, a game status-checking function continuously monitors whether the enemy’s position overlaps with the player’s position and whether the player has collected all the foods.

## Comments
Some of the challenges I faced in this projects were:
1. **Joystick Malfunction:**
   - The joystick malfunctioned and stopped recognizing the right and down inputs
   - Replaced the joystick with four buttons to simulate directional controls
   - Implemented an interrupt-driven callback function to recognize the player moves real time and checked the time since the last input to debounce buttons
2. **Frames of the game being refreshed too often leading to graphical issues:**
   - Only updated the display when there are changes to the game state by using a global display flag
3. **Sound functions using HAL_Delay()**
   - Cannot be used during the game, but before or after the game
