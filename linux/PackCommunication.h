#ifndef __PACK_COMMUNICATION_H
#define __PACK_COMMUNICATION_H

#include "Secex.h"

class PackCommunication {
private:
	static const char SFLAG;
	static const char EFLAG;
	static const char ESCC;
	static const char XORC;

private:
	int fd;
	int byteT;

public:
	PackCommunication();
	~PackCommunication();

	bool begin(char *path, int baud_rate=9600);
	void send(char *bytes, int size_b);
	bool recv(char *bytes, int &size_b);
	bool recv_wait(char *bytes, int &size_b);
};

#endif // #ifndef __PACK_COMMUNICATION_H