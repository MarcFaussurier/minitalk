#include <stdio.h>
#include <signal.h>

int main(int ac, char **av)
{
	int 	pid;
	int		i = 0;
	int		j = 0;

	pid = atoi(av[1]);
//	send_signal(pid, SIGUSR1);


	i = 0;
	while (av[2][i])
	{
		printf("-- %c\n", av[2][i]);
		j = 0;
		while (j < 8)
		{
			if ((av[2][i] & (1 << j)))
			{
				printf("1\n");
				kill(pid, SIGUSR2);
			}
			else
			{
				printf("0\n");
				kill(pid, SIGUSR1);
			}
			usleep(40);
			j += 1;
		}
		i += 1;
	}

}
