#ifndef   	_HZ_DEVICE_H
#define   	_HZ_DEVICE_H

int dev_open(const char *dev_name, 		void *args);
int dev_read( int fd, 	char *buf, 		int len);
int dev_write(int fd, 	char *buf, 		int len);
int dev_lseek(int fd, 	int offset, 	int flag);
int dev_ioctl(int fd, 	int request, 	void *args);
int dev_enable(int fd, 	int flag);
int dev_close(int fd);

#endif
