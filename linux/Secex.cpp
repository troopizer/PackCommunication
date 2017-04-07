#include "Secex.h"

bool secex::block_read(int fd, char * buffer, int size)
{
  int chars_in_readed_serialB = 0;

  do {
    ioctl(fd, FIONREAD, &chars_in_readed_serialB);
  } while (chars_in_readed_serialB < size);

  int read_ = 0, readed = 0;
  do {
    read_ = read(fd, &buffer[readed], size-readed);
    if (read_ < 0) return false;
    readed += read_;
  } while (readed < size);

  return true;
}
bool secex::block_write(int fd, const char * buffer, int size)
{
  int written = 0, writed;

  do {
    writed = write(fd, &buffer[written], size-written);
    if (writed < 1) return false;
    written += writed;
  } while (written < size);

  return true;
}
bool secex::device_open(int fd)
{
  return fd > 0;
}
bool secex::emptySerial(int fd)
{
  int chars_in_readed_serialB = 0;
  ioctl(fd, FIONREAD, &chars_in_readed_serialB);
  return chars_in_readed_serialB == 0;
}
bool secex::atleast_in_serial(int fd, int n)
{
  int chars_in_readed_serialB = 0;
  ioctl(fd, FIONREAD, &chars_in_readed_serialB);
  return (n<1)? false: chars_in_readed_serialB > n-1; 
}


int secex::open_arduino(const char * path, int baudRate)
{
  int fd = open(path, O_RDWR | O_NOCTTY | O_NONBLOCK);
    
  if (fd != -1) {
    struct termios options;

    memset(&options,0,sizeof(options));

    switch (baudRate) {
      case 1200:
        cfsetispeed(&options, B1200);
        cfsetospeed(&options, B1200);
        break;
      case 4800:
        cfsetispeed(&options, B4800);
        cfsetospeed(&options, B4800);
        break;
      case 9600:
        cfsetispeed(&options, B9600);
        cfsetospeed(&options, B9600);     
        break;
      case 38400:
        cfsetispeed(&options, B38400);
        cfsetospeed(&options, B38400);        
        break;
      case 57600:
        cfsetispeed(&options, B57600);
        cfsetospeed(&options, B57600);        
        break;
      case 115200:
        cfsetispeed(&options, B115200);
        cfsetospeed(&options, B115200);         
        break;
      default:  
        cfsetispeed(&options, B9600);
        cfsetospeed(&options, B9600);         
        break;
    }

    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag &= ~CRTSCTS;
    options.c_cflag |= CS8 | CREAD | CLOCAL;
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;
    /*
    options.c_iflag=0;
    options.c_oflag=0;
    options.c_cflag=CS8|CREAD|CLOCAL|PARODD;
    options.c_lflag=0;
    */

    options.c_cc[VMIN]  = 1;
    options.c_cc[VTIME] = 0;

    tcsetattr(fd, TCSANOW, &options);

    /* Wait for the Arduino to reset */
    usleep(2000*1000);
    tcflush(fd, TCIOFLUSH);
  }

  return fd;
}
void secex::close_arduino(int fd)
{
  close(fd);
}
