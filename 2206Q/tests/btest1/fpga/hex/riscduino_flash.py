#!/usr/bin/env python3
#https://pyserial.readthedocs.io/en/latest/pyserial_api.html
#https://media.digikey.com/pdf/Data%20Sheets/Winbond%20PDFs/W25Q32FV.pdf

from pyftdi.ftdi import Ftdi
import pyftdi.serialext
import time
import sys, os
from array import array as Array
import binascii
from io import StringIO
import re


SPI_FLASH_CMD_FAST_SINGLE_READ = 0x4080000b   # 0x0B
SPI_FLASH_CMD_FAST_DUAL_READ  = 0x509400bb   # 0xBB
SPI_FLASH_READ_DATA_CMD =  SPI_FLASH_CMD_FAST_DUAL_READ

#SPI_FLASH_WRITE_DATA_CMD = 



if len(sys.argv) < 2:
   print("Usage: raptor_flash.py <file>")
   sys.exit()

file_path = sys.argv[1]

if not os.path.isfile(file_path):
   print("File not found.")
   sys.exit()

# This is roundabout but works. . .
s = StringIO()
Ftdi.show_devices(out=s)
devlist = s.getvalue().splitlines()[1:-1]
gooddevs = []
for dev in devlist:
    url = dev.split('(')[0].strip()
    name = '(' + dev.split('(')[1]
    if name == '(FT232R USB UART)':
        gooddevs.append(url)
if len(gooddevs) == 0:
    print('Error:  No matching FTDI devices on USB bus!')
    Ftdi.show_devices()
    sys.exit(1)
elif len(gooddevs) > 1:
    print('Error:  Too many matching FTDI devices on USB bus!')
    Ftdi.show_devices()
    sys.exit(1)
else:
    print('Success: Found one matching FTDI device at ' + gooddevs[0])


port = pyftdi.serialext.serial_for_url(gooddevs[0], baudrate=9600,timeout=1)
if port.is_open:
   print("Serial Port is open.")


####################################################
# Send rm <addr> command and check the response
#  Return: Response Good  => '1' & <Read Data>
#  Return: Response Bad  => '0' & '00'
####################################################
def uartm_rm_cmd(addr):
    global port
    port.flushInput()
    cmd ='rm {:08x}\n'.format(addr)
    #print(cmd)
    port.write(cmd)
    byte_array = port.read_until(size=32)
    s_response = byte_array.decode()
    #print(byte_array)
    str_array = re.split('[ \n]',s_response)
    if (str_array[0] == 'Response:'):
        #print("Read  Addr: {:08x} Data:".format(addr) +str_array[1])
        return 1,int(str_array[1],16)
    else:
        print("Invalid Response:" + s_response + " Received")
        port.close();
        sys.exit()
        return 0,0x0

####################################################
# Send wm <addr> <data> command and check the response
#  Return: Response Good  => '1' 
#  Return: Response Bad  => '0' 
####################################################
def uartm_wm_cmd(addr,data):
    global port
    port.flushInput()
    cmd = 'wm {:08x} {:08x} \n'.format(addr,data)
    port.write(cmd)
    byte_array = port.read_until(size=32)
    #print(byte_array)
    s_response = byte_array.decode()
    s_response = s_response.strip('>') # To clean any previous response
    
    if (s_response == 'cmd success\n'):
        #print("Write Addr: {:08x} Data:{:08x}" .format(addr,data))
        return 1
    else:
        print("Invalid Response:" + s_response + " Received")
        port.close();
        sys.exit()
        return 0

### Reading Device ID(0x9F)
def user_flash_device_id():
    #uartm_wm_cmd(0x30080000,0x00000000)
    #uartm_wm_cmd(0x30080000,0x00000001)
    #uartm_wm_cmd(0x30080004,0x00001000)
    #uartm_wm_cmd(0x30020004,0x0000001F)
    uartm_wm_cmd(0x3000001c,0x00000001)
    uartm_wm_cmd(0x30000020,0x040c009f)
    status,read_data =uartm_rm_cmd(0x3000002c)
    print("Device ID:{:08x} ".format(read_data));


#############################################
#  Sector Erase Command            
#############################################
def user_flash_chip_erase():
    print("Flash Chip Erase: In Progress")
    uartm_wm_cmd(0x30080004,0x00001000)
    uartm_wm_cmd(0x3000001c,0x00000001)
    uartm_wm_cmd(0x30000020,0x00000006)
    uartm_wm_cmd(0x30000028,0x00000000)
    uartm_wm_cmd(0x3000001c,0x00000001)
    uartm_wm_cmd(0x30000020,0x002200d8)
    uartm_wm_cmd(0x30000024,0x00000000)
    uartm_wm_cmd(0x30000028,0x00000000)
    uartm_wm_cmd(0x3000001c,0x00000001)
    uartm_wm_cmd(0x30000020,0x040c0005)
    read_data = 0xFF;
    while (read_data != 0x00):
        status,read_data =uartm_rm_cmd(0x3000002c)
    print("Flash Chip Erasing: Done")


###########################
### Write 4 Byte
###########################
def user_flash_write(addr,data):
    print("Flash Write Addr: {:08x} Data:{:08x}" .format(addr,data))
    uartm_wm_cmd(0x30080004,0x00001000);
    uartm_wm_cmd(0x3000001c,0x00000001);
    uartm_wm_cmd(0x30000020,0x00000006);
    uartm_wm_cmd(0x30000028,0x00000000);
    #uartm_wm_cmd(0x3000001c,0x00000001);
    uartm_wm_cmd(0x30000020,0x04270002);
    uartm_wm_cmd(0x30000024,addr);
    uartm_wm_cmd(0x30000028,data);
    #uartm_wm_cmd(0x3000001c,0x00000001);
    uartm_wm_cmd(0x30000020,0x040c0005);
    read_data = 0xFF;
    while (read_data != 0x00):
        status,read_data =uartm_rm_cmd(0x3000002c)


#############################################
#  Page Read through Direct Access  (0X0B)          
#############################################
def user_flash_read(addr,exp_data):
    uartm_wm_cmd(0x30080004,0x00001000);
    uartm_wm_cmd(0x30000004,SPI_FLASH_READ_DATA_CMD);
    uartm_wm_cmd(0x30080004,0x00000000);
    status,rxd_data =uartm_rm_cmd(addr)
    if(exp_data == rxd_data):
        print("Flash Read Addr: {:08x} Data:{:08x} => Matched" .format(addr,exp_data))
    else:
        print("Flash Read Addr: {:08x} Exp Data:{:08x}  Rxd Data:{:08x} => FAILED" .format(addr,exp_data,rxd_data))
   
 
#############################################
#  User Reboot Command
#############################################
def user_reboot():
    print("Reseting up User Risc Core");
    uartm_wm_cmd(0x30080000,0x80000000); # Set Bit[31] = 1 to indicate user flashing to caravel
    uartm_wm_cmd(0x30080000,0x80000001);
    uartm_wm_cmd(0x30080004,0x00001000);
    uartm_wm_cmd(0x30020004,0x0000001F);
    
########################################
# User Risc Wake up
########################################
def user_risc_wakeup():
    print("Waking up User Risc Core");
    uartm_wm_cmd(0x30080000,0x80000000);
    uartm_wm_cmd(0x30080000,0x80000001);
    uartm_wm_cmd(0x30080004,0x00001000);
    uartm_wm_cmd(0x30020004,0x0000011F);



##############################
# Flash Write
##############################
def user_flash_progam():
    global file_path;
    print("User Flash Write Phase Started")
    with open(file_path, mode='r') as f:
        x = f.readline()
        nbytes = 0;
        total_bytes = 0;
        while x != '':
            if x[0] == '@':
                addr = int(x[1:],16)
                print('setting address to {}'.format(hex(addr)))
            else:
                #print(x)
                # values = bytearray.fromhex(x[0:len(x)-1])
                bytelist = re.split(' ',x[0:len(x)-1])
                #print(bytelist)
                dataout = 0x00;
                ncnt = 0;
                for data in bytelist:
                    if (data != ''):
                        dataout |= int(data, 16) << (8 * ncnt) 
                        ncnt = ncnt + 1
                        nbytes = nbytes+1
                        if(ncnt == 4):
                            user_flash_write(addr,dataout)
                            addr = addr+4;
                            ncnt = 0;
                            dataout = 0x00
    
            x = f.readline()
    
            if nbytes >= 256 or (x != '' and x[0] == '@' and nbytes > 0):
                total_bytes += nbytes
                print("addr {}: flash page write successful".format(hex(addr)))
                if nbytes > 256:
                    buf = buf[255:]
                    nbytes -= 256
                    print("*** over 256 hit")
                else:
                    buf = bytearray()
                    nbytes =0
    
        if nbytes > 0:
            total_bytes += nbytes
            # print('\n----------------------\n')
            # print(binascii.hexlify(buf))
            # print("\nnbytes = {}".format(nbytes))
            # print("addr {}: flash page write successful".format(hex(addr)))
    
    print("\ntotal_bytes = {}".format(total_bytes))

####################################
# Flash Read back and Verify#########
####################################
def user_flash_verify():
    global file_path;
    
    print("Flash Read back and Verify")
    with open(file_path, mode='r') as f:
        x = f.readline()
        nbytes = 0;
        total_bytes = 0;
        while x != '':
            if x[0] == '@':
                addr = int(x[1:],16)
                print('setting address to {}'.format(hex(addr)))
            else:
                #print(x)
                # values = bytearray.fromhex(x[0:len(x)-1])
                bytelist = re.split(' ',x[0:len(x)-1])
                #print(bytelist)
                dataout = 0x00;
                ncnt = 0;
                for data in bytelist:
                    if (data != ''):
                        dataout |= int(data, 16) << (8 * ncnt) 
                        ncnt = ncnt + 1
                        nbytes = nbytes+1
                        if(ncnt == 4):
                            user_flash_read(addr,dataout)
                            addr = addr+4;
                            ncnt = 0;
                            dataout = 0x00
    
            x = f.readline()
    
            if nbytes >= 256 or (x != '' and x[0] == '@' and nbytes > 0):
                total_bytes += nbytes
                print("addr {}: flash page write successful".format(hex(addr)))
                if nbytes > 256:
                    buf = buf[255:]
                    nbytes -= 256
                    print("*** over 256 hit")
                else:
                    buf = bytearray()
                    nbytes =0
    
        if nbytes > 0:
            total_bytes += nbytes
            # print('\n----------------------\n')
            # print(binascii.hexlify(buf))
            # print("\nnbytes = {}".format(nbytes))
            # print("addr {}: flash page write successful".format(hex(addr)))
    
    print("\ntotal_bytes = {}".format(total_bytes))



user_reboot(); 
status,read_data = uartm_rm_cmd(0x30020000)  # User Chip ID
user_flash_device_id()
user_flash_chip_erase()
user_flash_progam()
user_flash_verify()



#user_flash_write(0x000,0x11223344)
#user_flash_write(0x004,0x22334455)
#user_flash_read(0x000,0x11223344)
#user_flash_read(0x004,0x22334455)

user_risc_wakeup()


port.close();
if port.is_open:
   print("Serial Port is open.")
else:
   print("Serial Port is closed.")

