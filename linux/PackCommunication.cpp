#include "PackCommunication.h"

const char PackCommunication::SFLAG = 0x30;
const char PackCommunication::EFLAG = 0x31;
const char PackCommunication::ESCC  = 0x32;
const char PackCommunication::XORC  = 0x20;

PackCommunication::PackCommunication():
	fd(0),
	byteT(1000000)
{}
PackCommunication::~PackCommunication()
{}

bool PackCommunication::begin(const char *path, int baud_rate)
{
	fd = secex::open_arduino(path, baud_rate);
	byteT = 1000000/baud_rate;
	return secex::device_open(fd);
}

void PackCommunication::send(const char *bytes, int size_b)
{
	char c;
	secex::block_write(fd, &SFLAG, 1);
	for (int i=0;i<size_b;i++) {
		c = (bytes[i]);
		if (c == SFLAG || c == EFLAG || c == ESCC) {
			c ^= XORC;
			secex::block_write(fd, &ESCC, 1);
		}
		secex::block_write(fd, &c, 1);
	}
	secex::block_write(fd, &EFLAG, 1);
}

bool PackCommunication::recv(char *bytes, int &size_b)
{
	size_b = 0;
	if (!secex::atleast_in_serial(fd, 1)) 			return false;

	char c;
	if (!secex::block_read(fd, &c, 1) || c != SFLAG)	return false;
	do {
		if (!secex::block_read(fd, &c, 1))
			break;
		if (c == ESCC) {
			if (!secex::block_read(fd, &c, 1))
				break;
			c ^= XORC;
		}
		if (c == EFLAG) break;
		bytes[size_b++] = c;
	} while (1);

	return c==EFLAG;
}

bool PackCommunication::recv_wait(char *bytes, int &size_b)
{
	do {
		while (!secex::atleast_in_serial(fd, 1)) usleep(byteT);
		if (!recv(bytes, size_b)) return false;
	} while (size_b == 0);
	return true;
}