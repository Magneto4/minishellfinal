/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 22:30:54 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/10/28 17:03:29 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/readline.h>

extern int	g_ret;

int	deal_arguments_of_export(t_token *t)
{
	char	*new;

	new = NULL;
	if (t->next->type != T_WORD && t->next->type != T_NULL)
	{
		t = t->next;
		if (t->next->type == T_WORD)
			t->type = T_WORD;
	}
	while (are_words(2, t) && ft_strchr(t->str, '='))
	{
		new = ft_strjoin(t->str, t->next->str);
		if (!new)
			return (2);
		ft_token_remove_and_connect(&t);
		t->str = new;
	}
	return (0);
}

int	export_merge(t_token *t)
{
	int		is_bool;

	is_bool = is_command(t->next->str, "export");
	if (is_bool == 2)
		return (2);
	t = t->next;
	if (t->str && is_bool)
		change_everything_to_word(t->next);
	while (t && t->type != T_NULL)
	{
		if (t->str && is_bool && t->type != T_SPACE)
		{
			t = t->next;
			if (t->type == T_NULL)
				return (0);
			if (t->next->type == T_DOLLAR)
				return (0);
			if (deal_arguments_of_export(t) == 2)
				return (2);
		}
		t = t->next;
	}
	return (0);
}

void	syntax_analysis2(t_token *t, char **envp)
{
	if (!word_expension(t, envp))
		free_and_exit(t, envp);
	if (merge_word(t) == 2)
		free_and_exit(t, envp);
	if (export_merge(t) == 2)
		free_and_exit(t, envp);
	if (merge_word(t) == 2)
		free_and_exit(t, envp);
	if (remove_space_token(t) == 2)
		free_and_exit(t, envp);
}

int	set_global_and_ret_int(int global, int ret)
{
	g_ret = global;
	return (ret);
}

int	syntax_analysis(t_token *t, char **envp)
{
	t_token	*ret;

	if (t->next->type == T_NULL)
		return (1);
	syntax_analysis2(t, envp);
	ret = check_heredoc(t, envp);
	if (!ret)
	{
		if (g_ret == BAD_MALLOC)
		{
			perror("");
			return (BAD_MALLOC);
		}
		return (1);
	}
	if (t->next->type == T_NULL)
		return (0);
	ret = syntax_pipeline(t->next);
	if (t->next->type == T_NULL)
		return (1);
	if (!ret)
		return (set_global_and_ret_int(SYNTAX_ERROR, 1));
	return (0);
}
