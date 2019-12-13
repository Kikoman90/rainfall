#include <unistd.h>
#include <stdio.h>
#include <string.h>

char	*p(char *str, char *sep)
{
	char	input[4096];

	puts(sep);
	read(0, input, 4096);
	*strchr(input, '\n') = '\0';
	return (strncpy(str, input, 20));
}

char	*pp(char *buff)
{
	unsigned int	buff_len;
	char		str1[20];
	char		str2[20];

	p(str1, " - ");
	p(str2, " - ");
	strcpy(buff, str1);
	buff_len = strlen(buff);
	buff[buff_len] = ' ';
	return (strcat(buff, str2));
}

int	main(void)
{
	char buff[42];
	pp(buff);
	puts(buff);
	return (0);
}
