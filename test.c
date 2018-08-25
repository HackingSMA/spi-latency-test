#include <stdio.h>
#include <stdint.h>


#ifdef _MSC_VER
#include <windows.h>
#define WAIT_A_BIT Sleep(100);
#else
#include <unistd.h>
#define WAIT_A_BIT usleep(100000);
#endif

#include <libMPSSE_spi.h>

int main(int argc, char **argv)
{
	FT_STATUS status;
	uint32_t totalChannelNum;
	ChannelConfig channelConf;
	void *devHandle = NULL;
	uint32_t channel = 0;

	Init_libMPSSE();
	status = SPI_GetNumChannels(&totalChannelNum);
	if (status != FT_OK)
	{
		fprintf(stderr, "SPI_GetNumChannels() failed: %d\n", status);
		return -1;
	}

	if (totalChannelNum < 1)
	{
		fprintf(stderr, "SPI_GetNumChannels() returned %d channels\n", totalChannelNum);
		return -1;
	}

	status = SPI_OpenChannel(0, &devHandle);
	if (status != FT_OK)
	{
		fprintf(stderr, "SPI_OpenChannel() failed: %d\n", status);
		return -1;
	}

	channelConf.ClockRate = 12000000;
	channelConf.LatencyTimer = 2;
	channelConf.configOptions = SPI_CONFIG_OPTION_MODE0 | SPI_CONFIG_OPTION_CS_DBUS3 | SPI_CONFIG_OPTION_CS_ACTIVELOW;
	channelConf.Pin = 0x00000000;    /*FinalVal-FinalDir-InitVal-InitDir (for dir 0=in, 1=out)*/

	status = SPI_InitChannel(devHandle, &channelConf);
	if (status != FT_OK)
	{
		fprintf(stderr, "SPI_InitChannel() failed: %d\n", status);
		return -1;
	}

	printf("opened channel %d, running test...\n", channel);
	while (1)
	{
		SPI_ToggleCS(devHandle, 1); // activate CS (low)
		SPI_ToggleCS(devHandle, 0); // de-activate CS (high)

		// wait
		WAIT_A_BIT
	}

	return 0;
}