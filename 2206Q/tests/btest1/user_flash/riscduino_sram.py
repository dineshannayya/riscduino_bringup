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
SPI_FLASH_READ_DATA_CMD =  SPI_FLASH_CMD_FAST_SINGLE_READ

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

###########################
### Configuring SRAM Access
###########################

def user_sram_config():
    uartm_wm_cmd(0x30080004,0x00001000)
    uartm_wm_cmd(0x3000000C,0x30800003) #fix the Reset Value SPI SRAM READ Config 
    uartm_wm_cmd(0x30080004,0x00000800) # Setting Indirect Base Address to enable SRAM access


###########################
### SPI SRAM 4 Byte Write
###########################

def user_sram_write_data(addr,data):
    print("SRAM Write Addr: {:08x} Data:{:08x}" .format(addr,data))
    uartm_wm_cmd(addr,data);


#############################################
#  SPI SRAM 4 Byte Read
#############################################

def user_sram_read_data(addr,exp_data):
    status,rxd_data =uartm_rm_cmd(addr)
    if(exp_data == rxd_data):
        print("SRAM Read Addr: {:08x} Data:{:08x} => Matched" .format(addr,exp_data))
    else:
        print("SRAM Read Addr: {:08x} Exp Data:{:08x}  Rxd Data:{:08x} => FAILED" .format(addr,exp_data,rxd_data))
   
 
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
# SRAM WRITE Write
##############################
def user_sram_program():
    global file_path;
    print("User SPI SRAM Write Phase Started")
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
                            user_sram_write_data(addr,dataout)
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
# SRAM Read back and Verify#########
####################################
def user_sram_verify():
    global file_path;
    
    print("SRAM Read back and Verify")
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
                            user_sram_read_data(addr,dataout)
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



#uartm_wm_cmd(0x30080000,0x80000000)
#uartm_wm_cmd(0x30080000,0x80000001)
#uartm_wm_cmd(0x30020004,0x00000003)
#uartm_wm_cmd(0x30080004,0x00001000)
#uartm_rm_cmd(0x30020000)
#
##send reset command to switch to SINGLE PHASE
##wb_user_core_write(`ADDR_SPACE_QSPI+`QSPIM_IMEM_CTRL1,{16'h0,1'b0,1'b0,4'b0000,P_MODE_SWITCH_IDLE,P_QUAD,P_QUAD,4'b0100});
##wb_user_core_write(`ADDR_SPACE_QSPI+`QSPIM_IMEM_CTRL2,{8'h0,2'b00,2'b00,P_FSM_C,8'h00,8'hFF});
##wb_user_core_write(`ADDR_SPACE_QSPI+`QSPIM_IMEM_WDATA,32'h0);
#
#
##uartm_wm_cmd(0x3000001c,0x000000a4)
##uartm_wm_cmd(0x30000020,0x000000ff)
##uartm_wm_cmd(0x30000028,0x00000000)
#
##CS#2 SSPI Indiect Write DATA 
##wb_user_core_write(`ADDR_SPACE_QSPI+`QSPIM_IMEM_CTRL1,{16'h0,1'b0,1'b0,4'b0000,P_MODE_SWITCH_IDLE,P_SINGLE,P_SINGLE,4'b0100});
##wb_user_core_write(`ADDR_SPACE_QSPI+`QSPIM_IMEM_CTRL2,{8'h10,2'b00,2'b10,P_FSM_CAW,8'h00,8'h02});
##wb_user_core_write(`ADDR_SPACE_QSPI+`QSPIM_IMEM_ADDR,32'h00000000);
##wb_user_core_write(`ADDR_SPACE_QSPI+`QSPIM_IMEM_WDATA,32'h00112233);
##wb_user_core_write(`ADDR_SPACE_QSPI+`QSPIM_IMEM_WDATA,32'h44556677);
##wb_user_core_write(`ADDR_SPACE_QSPI+`QSPIM_IMEM_WDATA,32'h8899AABB);
##wb_user_core_write(`ADDR_SPACE_QSPI+`QSPIM_IMEM_WDATA,32'hCCDDEEFF);
#
#uartm_wm_cmd(0x3000001c,0x00000004)
#uartm_wm_cmd(0x30000020,0x04270002)
#uartm_wm_cmd(0x30000024,0x00000000)
#uartm_wm_cmd(0x30000028,0xAA112233)
#
#uartm_wm_cmd(0x3000001c,0x00000004)
#uartm_wm_cmd(0x30000020,0x04270002)
#uartm_wm_cmd(0x30000024,0x00000004)
#uartm_wm_cmd(0x30000028,0x44556677)
#
##CS#2 SSPI Indirect READ DATA 
##wb_user_core_write(`ADDR_SPACE_QSPI+`QSPIM_IMEM_CTRL1,{16'h0,1'b0,1'b0,4'b0000,P_MODE_SWITCH_IDLE,P_SINGLE,P_SINGLE,4'b0100});
##wb_user_core_write(`ADDR_SPACE_QSPI+`QSPIM_IMEM_CTRL2,{8'h10,2'b00,2'b10,P_FSM_CAR,8'h00,8'h03});
##wb_user_core_write(`ADDR_SPACE_QSPI+`QSPIM_IMEM_ADDR,32'h00000000);
##wb_user_core_read_check(`ADDR_SPACE_QSPI+`QSPIM_IMEM_RDATA,read_data,32'h00112233);
##wb_user_core_read_check(`ADDR_SPACE_QSPI+`QSPIM_IMEM_RDATA,read_data,32'h44556677);
##wb_user_core_read_check(`ADDR_SPACE_QSPI+`QSPIM_IMEM_RDATA,read_data,32'h8899AABB);
##wb_user_core_read_check(`ADDR_SPACE_QSPI+`QSPIM_IMEM_RDATA,read_data,32'hCCDDEEFF);
#
#uartm_wm_cmd(0x3000001c,0x00000004)
#uartm_wm_cmd(0x30000020,0x04230003)
#uartm_wm_cmd(0x30000024,0x00000000)
#uartm_rm_cmd(0x3000002c)
#
#uartm_wm_cmd(0x3000001c,0x00000004)
#uartm_wm_cmd(0x30000020,0x04230003)
#uartm_wm_cmd(0x30000024,0x00000004)
#uartm_rm_cmd(0x3000002c)
#
#### Direct Read
#uartm_wm_cmd(0x30080004,0x00001000)
#uartm_wm_cmd(0x3000000C,0x30800003) #fix the Reset Value 
#uartm_wm_cmd(0x30080004,0x00000800) # Setting Indirect Base Address
#uartm_wm_cmd(0x00002000,0x00112233)
#uartm_wm_cmd(0x00002004,0x44556677)
#uartm_wm_cmd(0x00002008,0x8899AABB)
#uartm_wm_cmd(0x0000200C,0xCCDDEEFF)
#uartm_rm_cmd(0x00002000)
#uartm_rm_cmd(0x00002004)
#uartm_rm_cmd(0x00002008)
#uartm_rm_cmd(0x0000200C)
#
#uartm_wm_cmd(0x30080004,0x00001000)
#uartm_rm_cmd(0x30020000)


#user_flash_write(0x000,0x11223344)
#user_flash_write(0x004,0x22334455)
#user_flash_read(0x000,0x11223344)
#user_flash_read(0x004,0x22334455)

user_reboot()
user_sram_config()
user_sram_program()
user_sram_verify()


port.close();
if port.is_open:
   print("Serial Port is open.")
else:
   print("Serial Port is closed.")

