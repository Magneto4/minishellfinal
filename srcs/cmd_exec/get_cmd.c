/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:59:34 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/28 15:38:46 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_cmd(char *cmd)
{
	struct stat	cmd_stat;

	stat(cmd, &cmd_stat);
	if (S_ISDIR(cmd_stat.st_mode))
	{
		errno = EISDIR;
		perror(cmd);
		free (cmd);
		return (126);
	}
	return (0);
}

int	test_path(char *cmd_name, char *path, char **cmd)
{
	char	*file_path;
	char	*cmd_path;

	file_path = ft_strjoin(path, "/");
	if (!file_path)
		return (BAD_MALLOC);
	cmd_path = ft_strjoin(file_path, cmd_name);
	free (file_path);
	if (!cmd_path)
		return (BAD_MALLOC);
	if (access(cmd_path, F_OK) >= 0)
	{
		*cmd = cmd_path;
		return (1);
	}
	free (cmd_path);
	return (0);
}

int	no_path(char *cmd_name)
{
	errno = 2;
	perror(cmd_name);
	return (CMD_NOT_FOUND);
}

int	give_cmd_with_path(char *cmd_name, char **paths, char **cmd)
{
	int		i;
	int		ret;

	if (access(cmd_name, F_OK) >= 0)
	{
		*cmd = ft_strdup(cmd_name);
		if (!(*cmd))
			return (BAD_MALLOC);
		return (check_cmd(*cmd));
	}
	if (!paths)
		return (no_path(cmd_name));
	i = 0;
	while ((paths)[i] && *cmd_name)
	{
		ret = test_path(cmd_name, paths[i], cmd);
		if (ret)
			return (ret * (ret == BAD_MALLOC));
		i ++;
	}
	write(STDERR_FILENO, cmd_name, ft_strlen(cmd_name));
	write(STDERR_FILENO, ": command not found\n", 20);
	return (CMD_NOT_FOUND);
}
