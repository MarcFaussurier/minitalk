#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "minitalk.h"

static	t_byte	*get_byte()
{
	static t_byte	b;

	return (&b);
}

void sig1(int sig)
{
	t_byte	*byte;

	byte = get_byte();
	write(1, "0\n", 2);
	byte->b &= ~(1 << byte->i++);
	if (byte->i == 8)
	{
		write(1, "-- ", 3);
		write(1, &byte->b, 1);
		write(1, "\n", 1);
		byte->i = 0;
	}
}

void sig2(int sig)
{
	t_byte	*byte;

	byte = get_byte();
	write(1, "1\n", 2);
	byte->b |= 1 << byte->i++;
	if (byte->i == 8)
	{
		write(1, "-- ", 3);
		write(1, &byte->b, 1);
		write(1, "\n", 1);
		byte->i = 0;
	}
}


int main()
{
	printf("minitalk server started with pid %i\n", getpid());
	signal(SIGUSR1, sig1);
	signal(SIGUSR2, sig2);
	while (1)
	{
		usleep(20);
	}
	// signal (SIGUSR1 .. ) == SIG_ERR
}
