#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minitalk.h"

static	t_minitalk	*get_minitalk()
{
	static t_minitalk	m;

	return (&m);
}

void	set_zero(char *c, int i)
{
	write(1, "0", 1);
	*c	&= ~(1 << i);
}

void 	set_one(char *c, int i)
{
	write(1, "1", 1);
	*c |= 1 << i;
}

void 	do_frame(void f(char *c, int i))
{
	t_minitalk	*m;

	m = get_minitalk();
	if (m->frame >= 0 && m->frame < sizeof(int) * 8)
	{
		f(((char*)(&(m->pid))) + (m->frame / 8), m->frame % 8);
		m->frame += 1;
	}
	else if (m->frame >= sizeof(int) * 8 && m->frame < 2 * sizeof(int) * 8)
	{
		f(((char*)(&(m->len))) + (m->frame / 8) - sizeof(int)
			, m->frame % 8);
		if (m->frame + 1 == 2 * sizeof(int) * 8)
		{
			m->o = malloc(m->len * sizeof(char));
			printf("[pid=%hhx %hhx %hhx %hhx len=%hhx %hhx %hhx %hhx]\n", 
				((char*)(&(m->pid)))[0],
				((char*)(&(m->pid)))[1],
				((char*)(&(m->pid)))[2],
				((char*)(&(m->pid)))[3],
				((char*)(&(m->len)))[0],
				((char*)(&(m->len)))[1],
				((char*)(&(m->len)))[2],
				((char*)(&(m->len)))[3]
			);
			printf("[pid=%i len=%i]\n", *(int*)(char*) &(m->pid), m->len);
		}
		m->frame += 1;
	}
	else 
	{
		f(m->o + (m->frame / 8) - 2 * sizeof(int), m->frame % 8);
		if (m->frame + 1 - 2 * sizeof(int) * 8 == m->len * 8)
		{
			write(1, m->o, m->len);
			kill(m->pid, SIGUSR1);
			if (m->o)
				free(m->o);
			*m = (t_minitalk) {0, 0, 0, 0};
			write(1, "\n", 1);
		}
		else
		{
			m->frame += 1;
		}
	}
}

void sig1(int sig)
{
	do_frame(set_zero);
}

void sig2(int sig)
{
	do_frame(set_one);
}


int main()
{
	printf("minitalk server started with pid %i\n", getpid());
	signal(SIGUSR1, sig1);
	signal(SIGUSR2, sig2);
	while (1)
	{
		usleep(80);
	}
}
