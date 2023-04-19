/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:31:53 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/28 16:06:55 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_pipes(t_processes *info, int i)
{
	int	ret;

	ret = 0;
	if (i > 0)
		ret = dup2(info->pipe_fds[i - 1][0], STDIN_FILENO);
	if (ret >= 0 && i < info->number_of_pipes)
		ret = dup2(info->pipe_fds[i][1], STDOUT_FILENO);
	close_pipes(info);
	return ((ret < 0) * FAILED_DUP);
}

int	l_redirect(t_token *token)
{
	int	fd;

	if ((token->str)[1])
		fd = open(token->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(token->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	token = token->next;
	if (fd > 0)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			close (fd);
			return (-2);
		}
		close (fd);
	}
	return (fd);
}

int	redirect(t_token *token)
{
	int	fd;

	fd = 0;
	if (token->type == T_R_REDIRECT)
		fd = l_redirect(token);
	else if (token->type == T_L_REDIRECT)
	{
		fd = open(token->next->str, O_RDONLY);
		token = token->next;
		if (fd > 0)
		{
			if (dup2(fd, STDIN_FILENO) < 0)
			{
				close (fd);
				return (-2);
			}
			close (fd);
		}
	}
	return (-1 * (fd < 0));
}

int	redirections(t_token *token)
{
	int	fd;

	while (token->type != T_NULL && token->type != T_PIPE)
	{
		fd = redirect(token);
		if (fd > 0)
			token = token->next;
		if (fd == -1)
			return (perror(token->next->str), FAILED_OPEN);
		if (fd == -2)
			return (FAILED_DUP);
		else if (fd)
			close(fd);
		if (token->type)
			token = token->next;
	}
	return (0);
}
