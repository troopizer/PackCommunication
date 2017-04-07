///////////////////////////////////////////////////////////////////////////////
// Linux Serial Communication Library
//

#ifndef SERIAL_COMMUNICATION_EXTENTIONS_H
#define SERIAL_COMMUNICATION_EXTENTIONS_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

namespace secex {

int open_arduino(const char * path, int baudRate);
void close_arduino(int fd);
bool device_open(int fd);

bool block_read(int fd, char * buffer, int size);
bool block_write(int fd, const char * buffer, int size);

bool emptySerial(int fd);
bool atleast_in_serial(int fd, int n);

}

#endif // SERIAL_COMMUNICATION_EXTENTIONS_H