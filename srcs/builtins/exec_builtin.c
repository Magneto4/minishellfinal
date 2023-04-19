/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:43:22 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/27 16:00:44 by eniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	prepare_builtin(t_token *token, t_processes *info)
{
	char	**argv_exec;
	int		ret;

	ret = 0;
	if (info->number_of_pipes)
		close_pipes(info);
	argv_exec = get_argv(token);
	if (!argv_exec)
		return (BAD_MALLOC);
	ret = exec_builtin(argv_exec, info);
	free_array(argv_exec);
	return (ret);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "cd\0", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd\0", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo\0", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env\0", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export\0", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset\0", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit\0", 5) == 0)
		return (1);
	return (0);
}

int	exec_builtin(char **argv, t_processes *info)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(argv[0], "cd\0", 3) == 0)
		ret = cd(info->envp, argv);
	else if (ft_strncmp(argv[0], "pwd\0", 4) == 0)
		ret = pwd();
	else if (ft_strncmp(argv[0], "echo\0", 5) == 0)
		ret = echo(argv);
	else if (ft_strncmp(argv[0], "env\0", 4) == 0)
		ret = env(argv, *(info->envp));
	else if (ft_strncmp(argv[0], "export\0", 7) == 0)
		ret = export(argv, info);
	else if (ft_strncmp(argv[0], "unset\0", 6) == 0)
		ret = unset(argv, info);
	else if (ft_strncmp(argv[0], "exit\0", 5) == 0)
		ret = ft_exit(argv);
	return (ret);
}

char	*get_last_cmd(t_token *token)
{
	t_token	*last_pipe;
	char	*cmd;

	last_pipe = token;
	while (token->type)
	{
		if (token->type == T_PIPE)
			last_pipe = token->next;
		token = token->next;
	}
	while (last_pipe->type == T_R_REDIRECT || last_pipe->type == T_L_REDIRECT)
		last_pipe = last_pipe->next->next;
	cmd = last_pipe->str;
	return (cmd);
}

int	no_fork(t_token *token)
{
	char	*cmd;

	cmd = get_last_cmd(token);
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "cd\0", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export\0", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset\0", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit\0", 5) == 0)
		return (1);
	return (0);
}
