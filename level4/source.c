#include <stdio.h>
#include <stdlib.h>

int	m;

void	p(char *str)
{
	printf(str);
}

void	n(void)
{
	char	buff[520];

	fgets(buff, 512, stdin);
	p(buff);
	if (m == 16930116)
	{
		system("/bin/cat /home/user/level5/.pass");
	}
	return ;
}

int	main(void)
{
	n();
	return (0);
}
