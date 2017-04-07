#include "PackCommunication.h"

static const char PackCommunication::SFLAG = 0x30;
static const char PackCommunication::EFLAG = 0x31;
static const char PackCommunication::ESCC  = 0x32;
static const char PackCommunication::XORC  = 0x20;

PackCommunication::PackCommunication(HardwareSerial &serial):
	ss(&serial),
	byteT(1000000)
{}
PackCommunication::~PackCommunication()
{}

bool PackCommunication::begin(int baud_rate)
{
	ss->begin(baud_rate);
	return ss;
}

void PackCommunication::send(char *bytes, int size_b)
{
	if (size_b < 1)	return;

	ss->write(SFLAG);
	ss->flush();
	char c;
	for (int i=0;i<size_b;i++) {
		c = (bytes[i]);
		if (c == SFLAG || c == EFLAG || c == ESCC) {
			ss->write(ESCC);
			c ^= XORC;
			ss->flush();
		}
		ss->write(c);
		ss->flush();
	}
	ss->write(EFLAG);
	ss->flush();
}

bool PackCommunication::recv(char *bytes, int &size_b)
{
	size_b = 0;
	if (ss->available() < 1) return false;

	char c;
	if (ss->readBytes(&c, 1) < 1 || c != SFLAG)	return false;
	do {
		while (ss->available() == 0) delayMicroseconds(byteT);
		ss->readBytes(&c, 1);
		if (c == ESCC) {
			while (ss->available() == 0) delayMicroseconds(byteT);
			ss->readBytes(&c, 1);
			c ^= XORC;
		}
		if (c == EFLAG) break;
		bytes[size_b++] = c;
	} while (1);

	return true;
}

bool PackCommunication::recv_wait(char *bytes, int &size_b)
{
	do {
		while (ss->available() == 0) delayMicroseconds(byteT);
		if (!recv(bytes, size_b)) return false;
	} while (size_b == 0);
	return true;
}
