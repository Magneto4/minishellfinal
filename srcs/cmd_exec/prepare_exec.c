/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:41:57 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/28 22:44:50 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_ret;

int	wait_children(t_processes *info)
{
	int	i;
	int	ret;

	g_ret = DONT_IGNORE;
	i = -1;
	ret = 0;
	while (++i < info->number_of_child)
	{
		if (ret != BAD_MALLOC)
			waitpid(info->ids[i], &ret, 0);
		else if (ret == BAD_MALLOC)
			waitpid(info->ids[i], NULL, 0);
	}
	return (ret);
}

void	error_maybe(int ret)
{
	if (ret && ret != EXIT && ret < FAILED_OPEN && ret != 1 && ret != 2)
		perror("");
}

int	execution(t_token *token, char ***envp)
{
	t_processes	*info;
	int			ret;
	int			ret2;

	info = init_info(token, envp);
	token = token->next;
	if (!info)
		return (g_ret);
	if (forks(info, token))
		return (FAILED_FORK);
	close_pipes(info);
	ret = 0;
	if (info->token->type != T_NULL)
		ret = prepare_builtin(info->token, info);
	ret2 = wait_children(info);
	if (info->token->type != T_NULL && ret != EXIT)
		g_ret = ret;
	else if (info->token->type == T_NULL && !(ret != \
	EXIT && (g_ret == 130 || g_ret == 131)))
		g_ret = WEXITSTATUS(ret2);
	if (ret != EXIT)
		ret = g_ret;
	free_struct (info);
	error_maybe(ret);
	return (ret * (ret <= EXIT && ret >= BAD_MALLOC));
}
