#ifndef __PACK_COMMUNICATION_H
#define __PACK_COMMUNICATION_H

#include <Boards.h>

class PackCommunication {
private:
	static const char SFLAG;
	static const char EFLAG;
	static const char ESCC;
	static const char XORC;

private:
	HardwareSerial *ss;
	int byteT;

public:
	PackCommunication(HardwareSerial &serial);
	~PackCommunication();

	bool begin(int baud_rate=9600);
	void send(char *bytes, int size_b);
	bool recv(char *bytes, int &size_b);
	bool recv_wait(char *bytes, int &size_b);
};

#endif // #ifndef __PACK_COMMUNICATION_H