

#Step-1: Changes in Make File
   #Step-1.1: Change the COM Port as per Your serial port 
   #DEV=/dev/cu.usbmodem34203
   DEV=/dev/ttyACM0
   
   #Step-1.1: Changed the Media folder
   #FLASH=/media/efabless/PYBFLASH/
   FLASH=/media/dinesha/NOD_F746ZG/

   #Step-1.2 Change
    #st-flash --connect-under-reset --format ihex write F746ZG_firmware.hex
    st-flash --reset --format ihex write F746ZG_firmware.hex


#Step-2 Install stlink
sudo pip install mpy-cross
sudo apt-get install libusb-1.0-0-dev


#Step-2.1: Clone and compile
git clone https://github.com/texane/stlink
cd stlink/
cmake .
make

#Step-2.2: Now we copy the built binaries to their place:
cd build/Release/bin
sudo cp st-* /usr/local/bin
cd ../lib
sudo cp *.so* /lib32

#Step-2.3: Copy udev rules:
cd ../../..
sudo cp config/udev/rules.d/49-stlinkv* /etc/udev/rules.d/

# Run 

make F746ZG
