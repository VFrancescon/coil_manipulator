# Library Subdirectory

All libraries developed for the project will be here.

As this is structured like a subdirectory, you could create a build folder here and build the libraries alone. 

Though [CppLinuxSerial](https://github.com/gbmhunter/CppLinuxSerial) will still need to be installed, as it is a dependency for all libraries.


# Tesla Meter Remarks

1. Acquire [CP210x_VCP Linxu Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
2. Plug Device into computer
3. Run `lsusb`
4. Identify the address for the Tesla Meter
5. From the source code for the VCP driver, follow the template and insert the Tesla Meter address found in point 4
6. `make`
7. `sudo cp cp210x.ko /lib/modules/<kernel-version>/kernel/drivers/usb/serial/ `
8. `sudo insmod /lib/modules/<kernel-version>/kernel/drivers/usb/serial/usbserial.ko `
9. `sudo insmod cp210x.ko `