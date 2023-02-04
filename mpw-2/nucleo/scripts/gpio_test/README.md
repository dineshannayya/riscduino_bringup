#Clean Previous Hex
make clean

#Re-Generated Hex file
make config_io_o.hex

#compile and copy the file to flash
make copy2

#Run the software
make run

