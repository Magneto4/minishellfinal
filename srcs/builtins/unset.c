/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:55:12 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/28 15:40:51 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_exist(char **envp, char *name)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, ft_strlen(name)) == 0 \
		&& envp[i][ft_strlen(name)] == '=')
			return (1);
		i ++;
	}
	return (0);
}

int	remove_env_var(t_processes *info, char *name)
{
	int		i;
	int		offset;
	char	**new_env;

	new_env = malloc(array_length(*(info->envp)) * sizeof(*new_env));
	if (!new_env)
		return (BAD_MALLOC);
	i = -1;
	offset = 0;
	while ((*(info->envp))[++i + offset])
	{
		if (ft_strncmp((*(info->envp))[i], name, ft_strlen(name)) == 0 \
		&& (*(info->envp))[i][ft_strlen(name)] == '=')
			offset = 1;
		if (!(*(info->envp))[i + offset])
			break ;
		new_env[i] = ft_strdup((*(info->envp))[i + offset]);
		if (!new_env[i])
			return (free_array(new_env), BAD_MALLOC);
	}
	new_env[i] = NULL;
	free_array (*(info->envp));
	*(info->envp) = new_env;
	return (0);
}

int	unset(char **argv, t_processes *info)
{
	int		ret;

	argv ++;
	while (*argv)
	{
		if (check_exist(*(info->envp), *argv))
		{
			ret = remove_env_var(info, argv[0]);
			if (ret)
				return (ret);
		}
		argv ++;
	}
	return (0);
}
