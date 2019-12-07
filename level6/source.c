#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void	m(void)
{
	puts("Nope");
}

void	n(void)
{
	system("/bin/cat /home/user/level7/.pass");
}

int	main(int argc, char **argv)
{
	void	*ptr;
	void	(**func)();

	ptr = malloc(64);
	func = malloc(4);

	*func = &m;
	strcpy(ptr, argv[1]);
	(*func)();
	return (0);
}
