/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:05:28 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/28 16:01:23 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_ret;

int	export_arg_2(t_processes *info, char *name, char *value, char *arg)
{
	int		ret;
	char	**temp;

	ret = change_env(info->envp, name, value);
	free(name);
	free(value);
	if (ret && ret != MISSING_ENV)
		return (ret);
	if (ret == 0)
		return (0);
	temp = array_dup(*(info->envp));
	if (!temp)
		return (BAD_MALLOC);
	free_array(*(info->envp));
	*(info->envp) = array_append(temp, arg);
	if (!*(info->envp))
	{
		*(info->envp) = temp;
		return (BAD_MALLOC);
	}
	free_array(temp);
	return (0);
}

int	check_name(char *var)
{
	int	i;

	if (('0' <= *var && *var <= '9') || *var == '=')
	{
		write(2, var, ft_strlen(var));
		write(2, ": not a valid identifier\n", 25);
		return (1);
	}
	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (0);
		if (!(ft_isalnum(var[i])) && var[i] != '_')
		{
			write(2, var, ft_strlen(var));
			write(2, ": not a valid identifier\n", 25);
			return (1);
		}
		i ++;
	}
	return (1);
}

int	export_arg(t_processes *info, char *var)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (var[i] && (i == 0 || var[i - 1] != '='))
		i ++;
	name = malloc ((i + 1) * sizeof(*name));
	if (!name)
		return (BAD_MALLOC);
	i = 0;
	while (var[i] != '=')
	{
		name[i] = var[i];
		i ++;
	}
	name[i] = '\0';
	value = ft_strdup(var + i);
	if (!value)
	{
		free (name);
		return (BAD_MALLOC);
	}
	return (export_arg_2(info, name, value, var));
}

int	export(char **argv, t_processes *info)
{
	int		j;
	int		ret;
	int		ret2;

	j = 1;
	ret = 0;
	ret2 = 0;
	while (argv[j] && (!ret || ret != 1))
	{
		if (check_name(argv[j]) == 0)
			ret = export_arg(info, argv[j]);
		else
			ret2 = 1;
		j ++;
	}
	return (ret2 * (!ret) + ret);
}
