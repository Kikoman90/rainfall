#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	FILE	*fd;
	char	buff[132] = {0};

	fd = fopen("/home/user/end/.pass", "r");
	if (!fd || argc != 2)
		return (-1);
	fread(buff, 1, 66, fd);
	buff[65] = 0;
	buff[atoi(argv[1])] = 0;
	fread(buff + 66, 1, 65, fd);
	fclose(fd);
	if (strcmp(buff, argv[1]) == 0)
		execl("/bin/sh", "sh", 0);
	else
		puts(buff + 66);
	return (0);
}
