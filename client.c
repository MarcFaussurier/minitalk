/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafaussu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:36:50 by mafaussu          #+#    #+#             */
/*   Updated: 2022/05/13 13:59:57 by mafaussu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "minitalk.h"

void	send_char(int pid, char c)
{
	int	j;

	j = 0;
	while (j < 8)
	{
		if ((c & (1 << j)))
		{
			kill(pid, SIGUSR2);
		}
		else
		{
			kill(pid, SIGUSR1);
		}
		usleep(160);
		j += 1;
	}
}

void	send_int(int server_pid, int i)
{
	char			*a;
	unsigned int	index;

	a = (char *) &i;
	index = 0;
	while (index < sizeof(int))
		send_char(server_pid, a[index++]);
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

	if (ac != 3)
		return (1);
	signal(SIGUSR1, send_confirmation);
	pid = ft_atoi(av[1]);
	send_int(pid, getpid());
	send_int(pid, ft_strlen(av[2]));
	i = 0;
	while (av[2][i])
		send_char(pid, av[2][i++]);
	while (1)
		usleep(4);
}
