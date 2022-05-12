#include <unistd.h>
#include <signal.h>

int ft_strlen(char *str)
{
	int	o;

	o = 0;
	while (*str++)
		o += 1;
	return (o);
}

void	send_char(int pid, char c)
{

	int	j;

	printf("-- %c\n", c);
	j = 0;
	while (j < 8)
	{
		if ((c & (1 << j)))
		{
			write(1, "1\n", 3);
			kill(pid, SIGUSR2);
		}
		else
		{
			write(1, "0\n", 3);
			kill(pid, SIGUSR1);
		}
		usleep(160);
		j += 1;
	}
}

void 	send_int(int server_pid, int i)
{
	char	*a; 
	int 	index;

	printf("sending int %i \n", i);
	a = (char*) &i;
	printf("[%hhx %hhx %hhx %hhx] \n", 
		a[0], a[1], a[2], a[3]);
	index = 0;
	while (index < sizeof(int))
		send_char(server_pid, a[index++]);
}

void	send_confirmation(int sig)
{
	write(1, "message sent successfully\n", 26);
}

int main(int ac, char **av)
{
	int 	pid;
	int		i;

	if (ac != 3)
		return 1;
	signal(SIGUSR1, send_confirmation);
	pid = atoi(av[1]);
	send_int(pid, getpid());
	send_int(pid, ft_strlen(av[2]));
	i = 0;
	while (av[2][i])
		send_char(pid, av[2][i++]);
	while (1)
	{
		usleep(120);
	}
}
