

############# Working with Windows 11 ############################
#Step-1: Install ST-Link USB Driver
https://www.st.com/en/development-tools/stsw-link009.html

#Ste-2: Get Microphython firmware for  Nucleo F746ZG
https://micropython.org/download/NUCLEO_F746ZG/

#Step-3: To Install STM Programmer Via st-link and Burn the MicroPython Firmware into Nucleo board
https://www.st.com/en/development-tools/stm32cubeprog.html#get-software


#Step-4: Open the Tera-Temp with Baud Rate: 115200, Apply nucleo Black push to reset the STM32
You will notice MicroPhyton Prompt

#PStep-5: Python IDE for development and debug(Available in windows & ubuntu)
https://thonny.org/


### Expected Signature  ###########
   mfg        = 0456
   product    = 11
   project ID = 00000000 -- ??
   JEDEC      = 0xef4016

JEDEC = 0xef4016 is corresponding to Winbond Serial Flash (0xeF) + 25Q32JV-IQ/JQ (0x4016)


# Documentation

#Nucleo F746ZG Board Documentation

https://www.st.com/resource/en/user_manual/um1974-stm32-nucleo144-boards-mb1137-stmicroelectronics.pdf

#MicriPython SPI
https://docs.micropython.org/en/latest/library/machine.SPI.html

#MicrpPython Example
https://youtu.be/a_G3WqjfPBA

#Winbond Flash Data sheet
https://www.winbond.com/resource-files/w25q32jv%20revg%2003272018%20plus.pdf

# Caravel Nucleo Schematic
https://raw.githubusercontent.com/efabless/caravel_board/main/hardware/caravel_Nucleo/caravel_Nucleo.pdf

