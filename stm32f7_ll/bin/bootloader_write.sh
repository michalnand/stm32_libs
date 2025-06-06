#st-link option
#https://github.com/stlink-org/stlink/
#st-flash --connect-under-reset write build.bin 0x8000000


#USART bootloader option
#https://pypi.org/project/stm32loader/
#serial TX to MCU RX (PA10).
#serial RX to MCU TX (PA9).
#serial DTR to MCU RESET.
#serial RTS to MCU BOOT0 (or BOOT0 to 3.3V).
#MCU BOOT1 to GND and press reset
#python3 stm32loader.py -e -w -v -b 115200 -p /dev/tty.usbserial-AM01VGIA  build.bin
#python3 stm32loader.py -e -w -v -b 115200 -p /dev/tty.usbserial-0001  build.bin
python3 stm32loader.py -e -w -v -b 115200 -p /dev/tty.usbserial-10  build.bin




#DFU USB bootloader option 
#https://gitlab.com/dfu-util/dfu-util
#MCU BOOT1 to GND and press reset
#sudo dfu-util -d 0483:df11 -c 1 -i 0 -a 0 -s 0x08000000 -D build.bin
  
