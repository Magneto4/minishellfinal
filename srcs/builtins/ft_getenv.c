/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:04:17 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/20 16:22:29 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_getenv(char **envp, char *var, char **res)
{
	char	**split;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
			break ;
		i ++;
	}
	if (!envp[i])
		return (MISSING_ENV);
	split = ft_split(envp[i], '=');
	if (!split)
		return (BAD_MALLOC);
	if (!split[1])
		*res = ft_strdup("\0");
	else
		*res = ft_strdup(split[1]);
	free_array(split);
	if (!*res)
		return (BAD_MALLOC);
	return (0);
}
