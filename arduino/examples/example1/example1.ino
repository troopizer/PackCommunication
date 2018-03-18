#include <PackCommunication.h>

char buff[256];
int size_b;

void setup ()
{
	Serial.begin(115200);

	Paco.begin(Serial);
}

void loop ()
{
	if (Paco.recv_wait(buff, size_b)) {
		Paco.send(buff, size_b);
	}
}
