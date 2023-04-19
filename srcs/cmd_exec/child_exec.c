/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:49:27 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/28 22:19:13 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_ret;

int	forks(t_processes *info, t_token *token)
{
	int	i;

	i = 0;
	while (i < info->number_of_child)
	{
		(info->ids)[i] = fork();
		if ((info->ids)[i] == 0)
			child_process(token, info, i);
		if ((info->ids)[i] < 0)
		{
			free_struct(info);
			return (FAILED_FORK);
		}
		while (token->type != T_PIPE && token->type != T_NULL)
			token = token->next;
		if (token->type == T_PIPE)
			token = token->next;
		i ++;
	}
	info->token = token;
	return (0);
}

char	**get_argv(t_token *token)
{
	char	**argv;
	char	**temp;

	argv = malloc(sizeof(*argv));
	if (!argv)
		return (NULL);
	*argv = NULL;
	while (token->type != T_NULL && token->type != T_PIPE)
	{
		if (token->type == T_L_REDIRECT || token->type == T_R_REDIRECT)
			token = token->next;
		else
		{
			temp = array_append(argv, token->str);
			if (!temp)
			{
				free_array(argv);
				return (NULL);
			}
			free_array(argv);
			argv = temp;
		}
		token = token->next;
	}
	return (argv);
}

void	exit_child(t_processes *info, int ret, char **argv_exec)
{
	if (argv_exec)
		free_array(argv_exec);
	free_token(&(info->token));
	free_array(*(info->envp));
	free_struct(info);
	if (errno == 13)
		exit (PERMISSION_DENIED);
	exit (ret * (ret != -1) + errno * (ret == -1));
}

void	check_ret(t_processes *info, int ret, char **argv_exec)
{
	if (ret)
		exit_child(info, ret, argv_exec);
}

int	child_process(t_token *token, t_processes *info, int i)
{
	char	**argv_exec;
	char	*cmd;
	int		ret;

	argv_exec = get_argv(token);
	if (!argv_exec)
		exit_child(info, BAD_MALLOC, argv_exec);
	ret = handle_pipes(info, i);
	check_ret(info, ret, argv_exec);
	ret = redirections(token);
	check_ret(info, ret, argv_exec);
	ret = 0;
	if (is_builtin(argv_exec[0]))
		ret = exec_builtin(argv_exec, info);
	else if (*argv_exec)
	{
		ret = give_cmd_with_path(argv_exec[0], info->paths, &cmd);
		check_ret(info, ret, argv_exec);
		g_ret = DONT_IGNORE;
		ret = execve(cmd, argv_exec, *(info->envp));
		perror(cmd);
		free (cmd);
	}
	return (exit_child(info, ret, argv_exec), 1);
}
