/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:01:20 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/26 13:09:48 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_ret;

int	ft_atoi_special(const char *nptr, int *nbr)
{
	int	i;
	int	s;
	int	n;

	i = 0;
	*nbr = 0;
	s = 1;
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == 32)
		i ++;
	if (nptr[i] == '-')
		s = -1;
	i += (nptr[i] == '+' || nptr[i] == '-');
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]))
			return (1);
		n = *nbr;
		*nbr = 10 * *nbr + s * (nptr[i] - '0');
		if ((n > 0 && *nbr <= n) || (n < 0 && *nbr >= n))
			return (1);
		i ++;
	}
	return (0);
}

int	ft_exit(char **argv)
{
	int	argc;
	int	exit_code;

	printf("exit\n");
	argc = array_length(argv);
	if (argc == 1)
	{
		g_ret = 0;
		return (EXIT);
	}
	if (ft_atoi_special(argv[1], &exit_code) > 0)
	{
		g_ret = 2;
		write(2, "exit: numeric argument required\n", 32);
		return (EXIT);
	}
	else if (argc == 2)
	{
		g_ret = exit_code;
		return (EXIT);
	}
	write(2, "exit: too many arguments\n", 25);
	g_ret = 2;
	return (1);
}
