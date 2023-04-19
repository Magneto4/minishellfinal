/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:02:06 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/27 16:47:47 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_ret;

int	count_pipes(t_token *token)
{
	int	i;

	i = 0;
	while (token->type)
	{
		if (token->type == T_PIPE)
			i ++;
		token = token->next;
	}
	return (i);
}

int	put_path(t_processes *info)
{
	int		ret;
	char	*paths;

	ret = ft_getenv(*(info->envp), "PATH", &paths);
	if (ret == BAD_MALLOC)
	{
		free(info->ids);
		free(info);
		return (1);
	}
	else if (ret == MISSING_ENV)
	{
		info->paths = NULL;
		return (0);
	}
	info->paths = ft_split(paths, ':');
	free (paths);
	if (!(info->paths))
	{
		free(info->ids);
		free(info);
		return (1);
	}
	return (0);
}

int	info_mallocs(t_processes *info)
{
	int		ret;

	info->ids = malloc(info->number_of_child * sizeof(*(info->ids)));
	if (!(info->ids))
	{
		free(info);
		return (BAD_MALLOC);
	}
	if (put_path(info))
		return (BAD_MALLOC);
	if (info->number_of_pipes == 0)
		info->pipe_fds = NULL;
	else
	{
		ret = create_pipes(info);
		if (ret)
		{
			free_array(info->paths);
			free(info->ids);
			free(info);
			return (ret);
		}
	}
	return (0);
}

t_processes	*init_info(t_token *token, char ***envp)
{
	t_processes	*info;

	info = malloc(sizeof(*info));
	if (!info)
		return (NULL);
	info->token = token;
	info->number_of_pipes = count_pipes(token->next);
	info->envp = envp;
	info->number_of_child = info->number_of_pipes + 1;
	if (no_fork(token->next))
		info->number_of_child -= 1;
	g_ret = info_mallocs(info);
	if (g_ret)
		return (NULL);
	return (info);
}
