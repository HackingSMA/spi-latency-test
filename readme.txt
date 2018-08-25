This folder contains a simple program to test the latency of the FTDI FT232H chip.
The program puts the chip into SPI mode and does the following in a loop:
	1) drive the CS pin low using SPI_ToggleCS()
	2) drive the CS pin high using SPI_ToggleCS()
	3) wait 100ms

An oscilloscope can be used to measure the time that the CS pin remains low, which is
presumably an indicator of the USB latency.