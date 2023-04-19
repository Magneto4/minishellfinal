/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:28:26 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/28 21:55:20 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_new_dir(char **pwd)
{
	int		i;

	i = 100;
	while (i < 4096)
	{
		*pwd = malloc(i * sizeof(*pwd));
		if (!*pwd)
			return (BAD_MALLOC);
		if (getcwd(*pwd, i * sizeof(**pwd)))
			break ;
		i += 100;
		free (*pwd);
	}
	if (i >= 4096)
		return (FAILED_FUN);
	return (0);
}

int	go_to_home(char **envp)
{
	int		ret;
	char	*home;

	ret = ft_getenv(envp, "HOME=", &home);
	if (ret)
	{
		if (ret == MISSING_ENV)
			write(STDERR_FILENO, "cd: HOME not set\n", 17);
		return (ret);
	}
	if (home[0])
	{
		ret = chdir(home);
		if (ret)
			perror(home);
	}
	free (home);
	return (ret);
}

int	change_pwd(char ***envp, char *cur_dir, int ret2)
{
	char	*new_dir;
	int		ret;

	ret = get_new_dir(&new_dir);
	if (ret)
	{
		if (!ret2)
			free (cur_dir);
		return (ret);
	}
	ret = change_env(envp, "PWD=", new_dir);
	free(new_dir);
	if (ret == BAD_MALLOC)
		return (ret);
	if (ret2)
		return (0);
	ret = change_env(envp, "OLDPWD=", cur_dir);
	free (cur_dir);
	return (ret * BAD_MALLOC);
}

int	change_to_dir(char *dir, int ret2)
{
	int	ret;

	if (ret2 == 0 || dir[0] == '/')
	{
		ret = chdir(dir);
		if (ret)
		{
			perror(dir);
			return (1);
		}
	}
	else
	{
		errno = 2;
		perror(dir);
		return (1);
	}
	return (0);
}

int	cd(char ***envp, char **argv)
{
	int		ret;
	int		ret2;
	char	*cur_dir;

	if (array_length(argv) > 2)
	{
		write(2, "cd: too many arguments\n", 23);
		return (TOO_MANY_ARGS);
	}
	ret2 = get_new_dir(&cur_dir);
	if (ret2 == BAD_MALLOC)
		return (BAD_MALLOC);
	if (!argv[1])
		ret = go_to_home(*envp);
	else
		ret = change_to_dir(argv[1], ret2);
	if (ret)
	{
		if (!ret2)
			free (cur_dir);
		return (ret);
	}
	ret = change_pwd(envp, cur_dir, ret2);
	return (ret);
}
