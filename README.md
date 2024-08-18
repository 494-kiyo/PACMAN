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

