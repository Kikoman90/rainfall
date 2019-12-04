#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int	main(int argc, char **argv)
{
	char	*dup;
	gid_t	egid;
	uid_t	euid;

	if (atoi(argv[1]) == 423)
	{
		dup = strdup("/bin/sh");
		egid = getegid();
		euid = geteuid();
		setresgid(egid, egid, egid);
		setresuid(euid, euid, euid);
		execv("/bin/sh", dup);
	}
	else
	{
		fwrite("No !\n", 1, 5, stderr);
	}
	return (0);
}
