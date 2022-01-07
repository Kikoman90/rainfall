#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*p(void)
{
	char	buff[64];
	void	*ret_addr;

	fflush(stdout);
	gets(buff);
	ret_addr = __builtin_return_address(0);
	if (((unsigned int)ret_addr & 0xb0000000) == 0xb0000000)
	{
		printf("(%p)\n", ret_addr);
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
