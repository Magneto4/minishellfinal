/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:59:07 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/28 16:08:16 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_pipes(int **pipe_fds)
{
	int	i;

	i = 0;
	while (pipe_fds[i])
	{
		free(pipe_fds[i]);
		i ++;
	}
	free(pipe_fds);
}

void	close_pipes(t_processes *info)
{
	int		j;

	if (!(info->number_of_pipes))
		return ;
	j = 0;
	while ((info->pipe_fds)[j])
	{
		close((info->pipe_fds)[j][0]);
		close((info->pipe_fds)[j][1]);
		j ++;
	}
}

int	create_pipes(t_processes *info)
{
	int	i;
	int	**pipe_fds;
	int	ret;

	ret = 0;
	pipe_fds = malloc((info->number_of_pipes + 1) * sizeof(*pipe_fds));
	if (!pipe_fds)
		return (1);
	i = -1;
	while (++i < info->number_of_pipes && ret == 0)
	{
		pipe_fds[i] = malloc (2 * sizeof(*pipe_fds));
		if (!(pipe_fds[i]))
			ret = BAD_MALLOC;
		else if (pipe(pipe_fds[i]) < 0)
			ret = FAILED_PIPE;
	}
	pipe_fds[i] = NULL;
	info->pipe_fds = pipe_fds;
	if (ret)
	{
		close_pipes(info);
		free_pipes(pipe_fds);
	}
	return (ret);
}
