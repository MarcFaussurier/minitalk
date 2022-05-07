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

int main(int ac, char **av)
{
	int 	pid;
	int		i;
	int		j;
	int		leni;
	char 	*len;

	if (ac != 3)
		return 1;
	pid = atoi(av[1]);
	leni = ft_strlen(av[2]);
	printf("-- leni: %i\n", leni);
	len = (char*) &leni;
	printf("%i %i %i %i\n", len[0], len[1], len[2], len[3]);
	i = 0;
	while (i < sizeof(int))
		send_char(pid, len[i++]);
	i = 0;
	while (av[2][i])
		send_char(pid, av[2][i++]);

}
