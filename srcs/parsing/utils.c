/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahjung <hyunahjung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:50:24 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/11/01 11:24:02 by hyunahjung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_ret;

void	free_token(t_token **t)
{
	t_token	*tmp;

	while (*t)
	{
		tmp = (*t)->next;
		if ((*t)->type != T_NULL && (*t)->type != T_START)
			free((*t)->str);
		free(*t);
		(*t) = tmp;
	}
	return ;
}

char	*check_if_start_by_num(t_token *t)
{
	char	*str;
	char	*tmp;
	t_token	*tmp2;

	str = t->str;
	if (ft_isdigit(str[0]))
	{
		str++;
		tmp = ft_strdup(str);
		if (!tmp)
			return (NULL);
		tmp2 = ft_tokennew(T_WORD, tmp);
		if (!tmp2)
			return (null_free(tmp));
		ft_token_insert(&t, tmp2);
		return (str);
	}
	return (str);
}

void	ft_modify_token_with_env(t_token *t, char *tmp)
{
	if (ft_strlen(tmp) == 0)
	{
		free(tmp);
		ft_token_remove_and_connect(&t);
	}
	else
	{
		free(t->str);
		t->str = tmp;
	}
}

int	write_token2file(t_token *heredoc_token, int fd)
{
	t_token	*token;

	token = heredoc_token->next;
	while (token && token->type != T_NULL)
	{
		write(fd, token->str, ft_strlen(token->str));
		token = token->next;
	}
	write(fd, "\n", 1);
	return (0);
}

int	is_alpha_or_digit_nor_including(char c, char *exclude)
{
	if ((ft_isalpha(c) || ft_isdigit(c)) && is_not_incld(c, exclude))
		return (1);
	return (0);
}
