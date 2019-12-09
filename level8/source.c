#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*auth;
char	*service;

int	main(void)
{
	char	str[128];

	while (1)
	{
		printf("%p, %p \n", auth, service);

		if (!fgets(str, 128, stdin))
			break;

		if (strncmp(str, "auth ", 5) == 0)
		{
			auth = malloc(4);
			auth[0] = 0;
			if (strlen(str + 5) < 30)
				strcpy((char *)auth, str + 5);
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
				fwrite("Password:\n", 1, 10, stdout);
		}
	}
	return (0);
}
