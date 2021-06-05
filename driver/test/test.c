#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<sys/select.h>



#define DATA_NUM (64)

int main(int argc , char *argv[])
{
	int fd ,i;
	int r_len, w_len;
	fd_set fdset;
	char buf[DATA_NUM] = "Hello world\n";
	memset(buf ,0 ,DATA_NUM);
	fd = open("/dev/hello", O_RDWR);

	printf("%d\r\n", fd);
	if(-1 == fd)
	{
		perror("open file error\r\n");
		return -1;
	}
	else
	{
		printf("open succese\r\n");

	}

	w_len = write(fd, buf, DATA_NUM);
	r_len = read(fd, buf, DATA_NUM);

	printf("%d %d \r\n", w_len, r_len);
	printf("%s \r\n", buf);

	return 0;
}

