/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 22:00:00 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/10/28 15:31:38 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <fcntl.h>
#include <readline/readline.h>

extern int	g_ret;

int	loop_heredoc(t_token *token, char **envp, int fd)
{
	t_token	*heredoc_token;
	char	*buf;

	buf = NULL;
	while (1)
	{
		buf = readline(">");
		if (!buf)
			break ;
		if (check_endcmd(token, buf, fd))
			break ;
		heredoc_token = heredoc_lexical_analysis(buf);
		if (!heredoc_token)
			return (BAD_MALLOC);
		if (!token_operation(heredoc_token, envp, fd, buf))
			return (BAD_MALLOC);
	}
	close(fd);
	if (read(STDIN_FILENO, NULL, 0) == -1)
		return (1);
	return (0);
}

t_token	*search_for_heredoc(t_token *token)
{
	while (token)
	{
		if (token->type == T_L_REDIRECT && ft_strlen(token->str) == 2)
		{
			token = token->next;
			if (token->type == T_WORD)
				return (token->prev);
		}
		token = token->next;
	}
	return (NULL);
}

void	heredoc_child(char *filename, t_token *t, t_token *heredoc, char **envp)
{
	int	fd;
	int	ret;

	ret = 0;
	fd = open(filename, O_CREAT | O_WRONLY, 0777);
	if (fd == -1)
	{
		perror("");
		exit (FAILED_OPEN);
	}
	run_signals(4);
	ret = loop_heredoc(heredoc, envp, fd);
	free_array(envp);
	free(filename);
	free_token(&t);
	close(fd);
	exit(ret);
}

int	check_heredoc2(t_token *t, t_token *heredoc, char *filename, char **envp)
{
	int		id;
	int		ret;
	t_token	*tmp;
	char	*str;

	ret = 0;
	id = fork();
	if (id < 0)
		bad_fork_exit(t, filename, envp);
	if (id == 0)
		heredoc_child(filename, t, heredoc, envp);
	waitpid(id, &ret, 0);
	free(heredoc->str);
	heredoc->str = ft_strndup("<", 1);
	if (!(heredoc->str))
		return (BAD_MALLOC);
	ft_token_remove_and_connect(&heredoc->next);
	str = ft_strdup(filename);
	if (!str)
		return (BAD_MALLOC);
	tmp = ft_tokennew(T_WORD, str);
	if (!tmp)
		return (BAD_MALLOC);
	ft_token_insert(&(heredoc), tmp);
	return (WEXITSTATUS(ret) * (g_ret != 130) + 1 * (g_ret == 130));
}

t_token	*check_heredoc(t_token *token, char **envp)
{
	t_token	*heredoc;
	char	*filename;
	int		ret;

	g_ret = IN_HEREDOC;
	heredoc = search_for_heredoc(token);
	while (heredoc)
	{
		filename = ft_create_tmp(".heredoc");
		if (!filename)
			ft_free_and_exit(token, envp);
		ret = check_heredoc2(token, heredoc, filename, envp);
		free(filename);
		if (ret == 1)
			return (NULL);
		if (ret == BAD_MALLOC)
			return (set_global_ret_null(BAD_MALLOC));
		heredoc = search_for_heredoc(token);
	}
	g_ret = 0;
	return (token);
}
