/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 22:31:05 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/11/01 13:34:50 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "../include/minishell.h"

int	g_ret;

int	check_syntax_error(t_token *token, char ***envp)
{
	if (!token)
		return (1);
	if (token->next->type == T_NULL)
		return (1);
	return (syntax_analysis(token, *envp));
}

int	shell(char *buf, char ***envp)
{
	t_token	*token;
	int		syntax_error;
	int		ret;

	syntax_error = 1;
	ret = 0;
	add_history(buf);
	token = lexical_analysis(buf, envp);
	if (token)
		syntax_error = check_syntax_error(token, envp);
	if (is_command(buf, "./minishell"))
		run_signals(5);
	else
		run_signals(2);
	if (!syntax_error)
		ret = execution(token, envp);
	else if (syntax_error == BAD_MALLOC)
		ret = syntax_error;
	free_token(&token);
	if (delete_tmpfile(".heredoc"))
	{
		free_array(*envp);
		exit(BAD_MALLOC);
	}
	return (ret);
}

int	loop_start(char ***envp)
{
	char	*buf;
	int		ret;

	ret = 0;
	while (1)
	{
		buf = NULL;
		run_signals(1);
		buf = readline("minishell$");
		if (!buf)
		{
			printf("exit\n");
			return (0);
		}
		if (is_command(buf, "./minishell"))
			run_signals(5);
		if (buf[0])
			ret = shell(buf, envp);
		if (ret)
			break ;
	}
	if (ret == 0 || ret == EXIT)
		return (0);
	return (ret);
}

char	**init_envp(char **envp)
{
	char	**envp2;
	char	*pwd;
	int		ret;

	if (*envp)
		envp2 = array_dup(envp);
	else
	{
		envp2 = malloc (2 * sizeof(*envp));
		if (!envp2)
			return (NULL);
		ret = get_new_dir(&pwd);
		if (ret)
			return (NULL);
		envp2[0] = ft_strjoin("PWD=", pwd);
		if (!(envp2[0]))
			return (free_array(envp2), NULL);
		envp2[1] = NULL;
	}
	return (envp2);
}

int	main(int ac, char **av, char **envp)
{
	char	**envp2;

	(void)av;
	if (ac > 1)
	{
		printf("please no arguments!");
		return (0);
	}
	envp2 = init_envp(envp);
	if (!envp2)
	{
		perror("");
		return (BAD_MALLOC);
	}
	g_ret = 0;
	loop_start(&envp2);
	free_array(envp2);
	return (g_ret);
}
