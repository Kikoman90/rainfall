#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int	main(int argc, char **argv)
{
	char	buff[40];
	int	i;

	(void)argc;
	if ((i = atoi(argv[1])) > 9)
		return (1);
	memcpy(buff, argv[2], i * 4);
	if (i == 1464814662)
		execle("/bin/sh", "sh", 0);
	return (0);
}
