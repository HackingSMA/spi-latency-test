You must have the following libraries and headers installed somewhere (e.g. /usr/local/lib, /usr/local/include):
libMPSSE-SPI.dylib - https://github.com/davidgs/OS-X-LibMPSSE-SPI
libftd2xx - http://www.ftdichip.com/Drivers/D2XX.htm

On OSX you may need to set an additional environment variable on osx to find the libraries at runtime, eg.
export DYLD_FALLBACK_LIBRARY_PATH=/user/local/lib

You can build with:
gcc test.c -o test -lMPSSE

On OSX you may need to do this, to prevent the VCP driver that ships with OSX from binding to the device:
sudo kextunload -b com.apple.driver.AppleUSBFTDI

On osx you may need to run the binary with sudo.
