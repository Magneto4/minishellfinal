/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 10:58:22 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/10/28 10:09:02 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_add_after_dollar_name(t_token *token, char *s, int i, int j)
{
	t_token	*tmp2;
	char	*tmp;

	tmp = ft_strndup(&s[i], j - i);
	if (!tmp)
		return (-2);
	tmp2 = ft_tokennew(T_WORD, tmp);
	if (!tmp2)
		return (ret_int_free(tmp, -2));
	ft_tokenadd_back(&token, tmp2);
	i = j;
	return (i);
}

int	heredoc_lexical_analysis2(t_token *token, char *s, int i)
{
	int		j;

	token->s = s;
	i = tok(token, is_not_incld, T_WORD, i, "$");
	i = tok(token, is_incld, T_DOLLAR, i, "$");
	if (i == -2)
		return (-2);
	if (s[i])
	{
		j = i;
		while (is_alpha_or_digit_nor_including(s[j], "$"))
			j++;
		if (j - i)
		{
			i = ft_add_after_dollar_name(token, s, i, j);
			if (i == -2)
				return (-2);
		}
	}
	return (i);
}

t_token	*heredoc_lexical_analysis(char *s)
{
	t_token	*token;
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	token = ft_tokennew(T_START, "T_START");
	if (!token)
		return (NULL);
	while (s[i])
	{
		i = heredoc_lexical_analysis2(token, s, i);
		if (i == -2)
			return (null_free_tok(token));
	}
	if (!s[i])
	{
		tmp = ft_tokennew(0, T_NULL);
		if (!tmp)
			return (null_free_tok(token));
		ft_tokenadd_back(&token, tmp);
	}
	return (token);
}
