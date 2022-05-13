/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafaussu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:27:44 by mafaussu          #+#    #+#             */
/*   Updated: 2022/05/13 15:20:37 by mafaussu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minitalk.h"

void	do_frame(void f(char *c, int i))
{
	static t_minitalk	m;

	if (m.frame >= 0 && m.frame < sizeof(int) * 8)
		f(((char *)(&(m.pid))) + (m.frame / 8), (m.frame)++ % 8);
	else if (m.frame >= sizeof(int) * 8 && m.frame < 2 * sizeof(int) * 8)
	{
		f(((char *)(&(m.len))) + (m.frame / 8) - sizeof(int), m.frame % 8);
		if (++(m.frame) == 2 * sizeof(int) * 8)
			m.o = malloc(m.len * sizeof(char));
	}
	else
	{
		f(m.o + (m.frame / 8) - 2 * sizeof(int), m.frame % 8);
		if (m.frame + 1 - 2 * sizeof(int) * 8 == m.len * 8)
		{
			write(1, m.o, m.len);
			kill(m.pid, SIGUSR1);
			if (m.o)
				free(m.o);
			m = (t_minitalk){0, 0, 0, 0};
			write(1, "\n", 1);
		}
		else
			m.frame += 1;
	}
}

void	sig1(int sig)
{
	(void) sig;
	do_frame(set_zero);
}

void	sig2(int sig)
{
	(void) sig;
	do_frame(set_one);
}

int	main(void)
{
	char	pid[65];

	ft_itoa(pid, getpid());
	write(1, "minitalk server started with pid ", 33);
	write(1, pid, ft_strlen(pid));
	write(1, "\n", 1);
	signal(SIGUSR1, sig1);
	signal(SIGUSR2, sig2);
	while (1)
		;
}
