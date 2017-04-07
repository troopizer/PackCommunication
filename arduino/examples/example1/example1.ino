#include <PackCommunication.h>

PackCommunication Paco(Serial);

char buff[256];
int size_b;

void setup ()
{
	Paco.begin(9600);
}

void loop ()
{
	
	if (Paco.recv_wait(buff, size_b)) {
		Paco.send(buff, size_b);
	}
	
	/*
	Paco.send("hola",4);
	delay(1000);
	*/
}