#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	language;

void	greetuser(char *buff)
{
	char	str[72];
	
	if (language == 1)
        	strcat(str, "Hyvää päivää ");
    	else if (language == 2)
        	strcat(str, "Goedemiddag! ");
    	else if (language == 0)
       		strcat(str, "Hello ");
	puts(strcat(str, buff));
}

int	main(int argc, char **argv)
{
	char	buff[72] = {0};
	char	*lang = NULL;

	if (argc != 3)
		return (1);
	strncpy(buff, argv[1], 40);
	strncpy(buff + 40, argv[2], 32);
	if ((lang = getenv("LANG")))
	{
		if (memcmp(lang, "fi", 2) == 0)
        		language = 1;
    		else if (memcmp(lang, "nl", 2) == 0)
       			language = 2;
	}
	greetuser(buff);
	return (0);
}
