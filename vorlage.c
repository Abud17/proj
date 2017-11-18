#include<stdio.h>
#include<wiringPi.h>
#include<wiringSerial.h>
#include<errno.h>
#include<stdlib.h>

int main()
{
	
	int fd = 0, count = 0;
	unsigned int nextTime = 100;
	// Initialize WiringPi library
	if ( wiringPiSetup() == -1 )
	{
		printf("Initialisation is failed");
		exit(1);		
	}
	// Initialize Serial Communication 
	if ((fd = serialopen ("/dev/ttyS0", 9600)) < 0)
	{
		// The strerror() function, which returns a pointer to the texual representation of the current errno value
		// FILE* stderr The standard errror stream 
		fprintf(stderr,"Unable to open serial device: %s\n",strerror(errno));
		return 1;
		
	}
	
	for (;;)
	{
		// Serial Communication
		// millis() return a number corresponding to the millisecond of prgram beginning.
		if (millis() > nextTime)
		{
			// Sends the nul-terminated string to the serial device identified by the given file descriptor
			
			serialPuts(fd, "U");
			// number of sending
			printf("\nout: %3d: ",count);
			fflush(stdout);
			//Time adjust of sending
			nextTime = millis() + 250;
			count++;
			// Read the RX if data is available 
			while (serialDataAvail(fd))
			{
				// Returns to the next character available in the serial device.
				// This call will block for up to 10 seconds if no data is available (when it will rerurn -1)
				
				printf(" -> %3d", serialGetchar(fd));
				fflush(stdout);
				
			}

			
		}
	}
	// Closses the device identified by the file descriptor given.
	serialClose(fd);
	
	return 0;
	
}
