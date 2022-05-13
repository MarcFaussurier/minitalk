/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafaussu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:36:50 by mafaussu          #+#    #+#             */
/*   Updated: 2022/05/13 15:23:52 by mafaussu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "minitalk.h"

int	send_char(int pid, char c)
{
	int	j;

	j = 0;
	while (j < 8)
	{
		if ((c & (1 << j)))
		{
			if (kill(pid, SIGUSR2))
				return (1);
		}
		else
		{
			if (kill(pid, SIGUSR1))
				return (1);
		}
		usleep(42);
		j += 1;
	}
	return (0);
}

int	send_int(int server_pid, int i)
{
	char			*a;
	unsigned int	index;

	a = (char *) &i;
	index = 0;
	while (index < sizeof(int))
		if (send_char(server_pid, a[index++]))
			return (1);
	return (0);
}

void	send_confirmation(int sig)
{
	(void) sig;
	write(1, "message sent successfully\n", 26);
	exit(0);
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	if (ac != 3 || !av[2][0])
		return (1);
	signal(SIGUSR1, send_confirmation);
	pid = ft_atoi(av[1]);
	if (send_int(pid, getpid())
		|| send_int(pid, ft_strlen(av[2])))
	{
		write(1, "invalid server pid\n", 19);
		return (1);
	}
	i = 0;
	while (av[2][i])
		if (send_char(pid, av[2][i++]))
		{
			write(1, "invalid server pid\n", 19);
			return (1);
		}
	while (1)
		;
	return (0);
}
