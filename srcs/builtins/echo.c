/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:47:14 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/25 12:23:09 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_n(char *str)
{
	if (!str)
		return (0);
	if (*str != '-')
		return (0);
	str ++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str ++;
	}
	return (1);
}

int	echo(char **argv)
{
	int	flag_n;
	int	i;

	flag_n = 0;
	argv ++;
	while (is_n(*argv))
	{
		flag_n = 1;
		argv ++;
	}
	i = 0;
	while (argv[i])
	{
		if (i > 0)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i ++;
	}
	if (flag_n == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
