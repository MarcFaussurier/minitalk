#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minitalk.h"

static	t_str	*get_str()
{
	static t_str	str;

	return (&str);
}

void	set_bit(unsigned char	b)
{
	t_str	*str;

	str = get_str();
	// parse msg len
	if (str->p < sizeof(int))
	{
		if (b == 0)
		{
			write(1, "len---0\n", 8);
			((char*)&(str->len))[str->p] &= ~(1 << str->i);
		}
		else
		{
			write(1, "len---1\n", 8);
			((char*)&(str->len))[str->p] |= 1 << str->i;
		}
	}
	// todo: parse pid
	// parse msg
	else
	{
		if (str->p == 4 && str->i == 0)
		{
			str->o = malloc(str->len);
		}

		if (b == 0)
		{
			str->o[str->p - sizeof(int)] &= ~(1 << str->i);
		}
		else
		{
			str->o[str->p - sizeof(int)] |= 1 << str->i;
		}
	}
	str->i += 1;

	if (str->i == 8)
	{
		str->i = 0;
		str->p += 1;
		printf("%i\n", str->p);
	}
	

	if (str->p == sizeof(int) && str->i == 0)
	{
		t_str	b;
	
	
		b.c1 = ((char*)&str->len)[0]; 
		b.c2 =	((char*)&str->len)[1];
		b.c3 =	((char*)&str->len)[2]; 
		b.c4 =	((char*)&str->len)[3]; 
		printf("blemn=%i\n", b.len);
		printf("%i %i %i %i\n",
				((char*)&str->len)[0], 
				((char*)&str->len)[1], 
				((char*)&str->len)[2], 
				((char*)&str->len)[3]); 
		printf("lemn=%i", str->len);
	}

	if (str->p - sizeof(int) == str->len)
	{
		write(1, str->o, str->len - sizeof(int));
		str->p = 0;
		str->i = 0;
		str->o = 0;
		str->len = 0;
		// send success msg
	}
}

void sig1(int sig)
{
	set_bit(0);
}

void sig2(int sig)
{
	set_bit(1);
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
