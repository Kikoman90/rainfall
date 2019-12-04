#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*p(void)
{
	char		buff[76];
	unsigned long	ret_addr;

	fflush(stdout);
	gets(buff);
	ret_addr = (unsigned long)__builtin_return_address(0);
	if ((ret_addr & 0xb0000000) == 0xb0000000)
	{
		printf("(%p)\n", (void*)ret_addr);
		exit(1);
	}
	puts(buff);
	return (strdup(buff));
}

int	main(int argc, char **argv)
{
	p();
	return (0);
}
