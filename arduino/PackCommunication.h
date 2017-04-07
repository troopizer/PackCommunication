#include "PackCommunication.h"

static const char PackCommunication::FLAG = 0x30;

PackCommunication::PackCommunication(HardwareSerial &serial):
	ss(serial),
	byteT(1000000)
{}
PackCommunication::~PackCommunication()
{}

bool PackCommunication::begin(int baud_rate, uint8_t config)
{
	ss.begin(baud_rate, config);
	return ss;
}

void PackCommunication::send(char *bytes, int size_b)
{
	char size_B[2] = {(char)(0xFF & size_b), (char)(0xFF & (size_b>>8))};

	ss.write(&FLAG, 1);
	ss.write(&size_B, 2);
	ss.write(bytes, size_b);
	ss.flush();
}