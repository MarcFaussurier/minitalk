/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafaussu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:35:57 by mafaussu          #+#    #+#             */
/*   Updated: 2022/05/13 13:36:31 by mafaussu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <unistd.h>

void	set_zero(char *c, int i)
{
	*c &= ~(1 << i);
}

void	set_one(char *c, int i)
{
	*c |= 1 << i;
}

int	ft_strlen(char *str)
{
	int	o;

	o = 0;
	while (*str++)
		o += 1;
	return (o);
}

int	ft_atoi(char *str)
{
	int	o;

	o = 0;
	while (*str >= '0' && *str <= '9')
	{
		o *= 10;
		o += *str - '0';
		str += 1;
	}
	return (o);
}

void	ft_itoa(char *out, unsigned int n)
{
	unsigned char	numlen;
	size_t			i;
	unsigned int	nb;

	if (n == 0)
	{
		*out = '0';
		out[1] = 0;
		return ;
	}
	numlen = 0;
	nb = n;
	while (nb && (++numlen))
		nb /= 10;
	numlen -= 1;
	i = 0;
	while (n)
	{
		out[numlen - i] = ('0' + n % 10);
		n /= 10;
		i += 1;
	}
	out[i] = '\0';
	return ;
}
