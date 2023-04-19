/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 10:55:22 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/10/28 20:31:37 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_ret;

int	ft_dq_lexical_analysis(t_token *token, int j)
{
	char	*s;

	s = token->s;
	while (s[j] && !(is_same(s[j], 34)))
	{
		if (s[j] == '$')
		{
			j = tok(token, is_incld, T_DOLLAR, j, "$");
			j = tok(token, is_incld, T_SPECIAL, j, "?");
			if (j == -2)
				return (-2);
			if (ft_isdigit(s[j]))
				j = tok_one_char(token, j, s[j], T_WORD);
			j = tok(token, is_not_incld, T_WORD, j, "?$\"\'<>|/");
			if (j == -2)
				return (-2);
		}
		j = tok(token, is_not_incld, T_WORD, j, "$\"");
		if (j == -2)
			return (-2);
	}
	return (j);
}

int	dq_analysis2(t_token *token, int j)
{
	char	*s;
	t_token	*tmp;

	s = token->s;
	tmp = NULL;
	if (is_same(s[j], 34))
	{
		tmp = ft_tokennew(T_WORD, ft_strdup("\0"));
		if (!tmp)
			return (-2);
		ft_tokenadd_back(&token, tmp);
	}
	j = ft_dq_lexical_analysis(token, j);
	if (j == -2)
		return (-2);
	return (j);
}

int	dq_analysis(t_token *token, int i)
{
	char	*s;

	if (i == -1 || i == -2)
		return (i);
	s = token->s;
	if (is_same(s[i], 34))
	{
		i++;
		if (ft_tokenlast(token)->type == T_DOLLAR)
		{
			if (!dollar_before_quote(token))
				return (-2);
		}
		i = dq_analysis2(token, i);
		if (i == -2)
			return (-2);
		if (if_null_fail(s[i]))
			return (-1);
		i++;
	}
	return (i);
}

int	sq_analysis2(t_token *token, int i)
{
	int		j;
	char	*tmp;
	char	*s;
	t_token	*tmp2;

	j = i;
	s = token->s;
	tmp2 = NULL;
	while (s[j] && s[j] != 39)
		j++;
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

int	sq_analysis(t_token *token, int i)
{
	char	*s;

	if (i == -1 || i == -2)
		return (i);
	s = token->s;
	if (s[i] && is_same(s[i], 39))
	{
		i++;
		if (ft_sq_lexical_analysis(token, i) == -2)
			return (-2);
		while (s[i] && !(is_same(s[i], 39)))
		{
			i = sq_analysis2(token, i);
			if (i == -2)
				break ;
		}
		if (i == -2)
			return (-2);
		if (if_null_fail(s[i]))
			return (-1);
		i++;
	}
	return (i);
}
