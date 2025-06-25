# Computer Interfacing and Embedded System
![alt text](https://github.com/Tanvir-Mahamood/Computer-Interfacing-and-Embedded-System2/blob/main/Arduino%20IDE/RGB.jpeg) 
## Components
| SI | Component name | Quantity | 
|---|---|---|
| 1 | STM32 Blue Pill (STM32F103C8T6) | 1 |
| 2 | ST Link V2 Programmer for STM32 | 1 |
| 3 | 10K Resistor | 10 |
| 4 | 220Ω resistors | 10 |
| 5 | Bread Board | 1 |
| 6 | Jumper Wire (Male to Male) | 20 |
| 7 | Multimeter | 1 |
| 8 | 2 pin Pushbutton | 5 |
| 9 | RED LED | 5 |
| 10 | GREEN LED | 5 |
| 11 | YELLOW LED | 5 |
| 12 | 3 pin RGB LED | 5 |
| 13 | 10kΩ potentiometer | 3 |
| 14 |  Photoresistor| 2|
| 15 | TMP36 Temperature Sensor | 1 |


## Software to be installed
1. Arduino IDE (2.3.1) [Here `1.8.18` has used] : [Download](https://github.com/arduino/arduino-ide/releases)
2. Keil uVision IDE (5.39.0.0) : [Download](https://www.keil.com/demo/eval/arm.htm) and [Installation Process](https://www.youtube.com/watch?v=buQtJjgw2pE)
3. ST-Link driver Install : [Download](https://www.st.com/en/development-tools/stsw-link009.html)
4. STM32 Cube Programmer Install : [Download](https://www.st.com/en/development-tools/stm32cubeprog.html)
5. Proteus [Download and Installation](https://www.youtube.com/watch?v=GCHmyCTLz5s)
6. Emulator8086 [Download](https://emu8086-microprocessor-emulator.en.softonic.com/download)

## Environment Setup
### Arduino IDE
1. Make sure Arduino IDE is installed.
2. Make sure the ST-Link driver is installed.
3. Make sure the STM32 Cube Programmer is installed.
4. Run Arduino IDE.
5. Open File > Preferences. Add

```
https://raw.githubusercontent.com/stm32duino/BoardManagerFiles/main/package_stmicroelectronics_index.json to Additional
```

to Additional Board Manager URLs. Select Ok.

6. Open `Tools > Board > Boards Manager`. Install Arduino `AVR Boards` and `STM32 MCU Based Boards`.
`pic2`
7. Connect ST-Link V2 and Blue Pill using the connector and insert ST-Link to USB. Make sure to check pinouts of your device before
connecting.
`GND -> GND
3V3 -> 3V3
SWCLK -> SWCLK
SWIO -> SWDIO`
8. Select board and configure:
`Tools > Board Generic STM32F1 series > STM32 boards group > Generic STM32F1 series` .<br>Again
`Tools > `<br>`
Board part number: "Bluepill F103C8" `<br>`
U(S)ART support: "Ennable (generic 'Serial')" `<br>`
USB support (if available): "None" `<br>`
USB speed (if available): "Low/Full Speed" `<br>`
Optimize: "Smallest(-Os default)" `<br>`
Debug Symbols and core logs: "None" `<br>`
C Runntime Library: "Newlib Nano(default)" `<br>`
Upload method: "STM32CubeProgrammer(SWD)"`
9. Write a program. Then build and upload.

|You may practice coading on|
|---|
| [WOKI](https://wokwi.com/projects/new/arduino-nano) |


### Keil uVision5
[Keil uVision package installation guide](https://youtu.be/TO85lArN1B8?si=K7zrRv7hrTyiRHGe)
> [!NOTE]
> Start from 10:00 minutes


[Start Keil project](https://youtu.be/LvfjFihNSgE?si=1y6YsQCeKM6bpcdX)
> [!NOTE]
> No need to configure simulation and XTAL, use either  Stm32f103c6 / stm32f103c8.


## 📄 License
This project is open source and available under the [Apache 2.0 License](LICENSE).