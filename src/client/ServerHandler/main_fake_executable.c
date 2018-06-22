
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	sig_handler(int signum)
{
	printf("CATCH SIG: %d\n", signum);
	exit(1);
}

int	main(int ac, char **av)
{
	printf("--start--\n");
	signal(SIGINT, sig_handler);
	for (int i = 0; av[i]; ++i) {
		printf("---> %d --> [%d]: '%s'\n", ac, i, av[i]);
	}
	char buff;
	while (read(0, &buff, 1) > 0);
	printf("--end--\n");
	return 0;
}