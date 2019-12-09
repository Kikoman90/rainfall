#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int	*auth;
char			*service;

int			main(void)
{
	char	str[128];
	int		i;

	while (42)
	{
		printf("%p, %p\n", auth, service);
		if (fgets(str, 128, stdin) == 0)
			return (0);
		if (strncmp(str, "auth ", 5) == 0)
		{
			auth = malloc(4);
			*auth = 0;
			if (strlen(str + 5) < 30)
				strcpy((char *)auth, &str[5]);
		}
		if (strncmp(str, "reset", 5) == 0)
			free(auth);
		if (strncmp(str, "service", 6) == 0)
			service = strdup(str + 7);
		if (strncmp(str, "login", 5) == 0)
		{
			if (auth[32] != 0)
				system("/bin/sh");
			else
				fwrite("Password:\n", 10, 1, stdout);
		}
	}
	return (0);
}
