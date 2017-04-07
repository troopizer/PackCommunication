#include <stdio.h>
#include <unistd.h>
#include "PackCommunication.h"

int main(int argc, char *argv[])
{
	char buffer[256];
	int size_b;
	PackCommunication paco;

	if (!paco.begin("/dev/ttyUSB0", 9600)) {
		printf("Couldn't open device\n");
		return 1;
	}
	printf("Device open\n");

	paco.send("sending", 6);
	for (;;usleep(50)) {
		if (paco.recv_wait(buffer, size_b)) {
			buffer[size_b] = '\0';
			printf("[%d] :: %s\n", size_b, buffer);
			sleep(1);
			paco.send("receiving", 9);
		}
		/*paco.recv(buffer, size_b);
		if (size_b > 0) {
			buffer[size_b] = '\0';
			printf("[%d] :: %s\n", size_b, buffer);
		}*/
	}

	return 0;
}