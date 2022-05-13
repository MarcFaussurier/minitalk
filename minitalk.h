/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafaussu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:34:49 by mafaussu          #+#    #+#             */
/*   Updated: 2022/05/13 13:35:46 by mafaussu         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

typedef struct s_minitalk
{
	unsigned int	frame;
	int				pid;
	int				len;
	char			*o;
}	t_minitalk;
void	set_zero(char *c, int i);
void	set_one(char *c, int i);
int		ft_strlen(char *str);
int		ft_atoi(char *str);
void	ft_itoa(char *str, unsigned int i);

#endif
