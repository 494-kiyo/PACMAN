# Pac-Man using an STM32F401RE

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

## LCD with PCF8574
