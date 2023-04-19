/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 22:30:51 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/10/28 17:49:52 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_ret;

int	add_token(t_token *t, int i, int j, int tt)
{
	t_token	*tmp;
	char	*str;
	char	*s;

	tmp = NULL;
	str = NULL;
	s = t->s;
	str = ft_strndup(&s[i], j - i);
	if (!str)
		return (-2);
	(void)tt;
	tmp = ft_tokennew(tt, str);
	if (!tmp)
		return (ret_int_free(str, -2));
	ft_tokenadd_back(&t, tmp);
	i = j;
	return (i);
}

int	tok(t_token *t, int (*f)(char, char*), int tt, int i, char *a)
{
	int		(*ptr)(char, char*);
	int		j;
	char	*s;

	if (i == -1 || i == -2)
		return (i);
	j = i;
	ptr = f;
	s = t->s;
	if (ptr(s[j], a))
	{
		while (ptr(s[j], a))
			j++;
		i = add_token(t, i, j, tt);
		if (i == -2)
			return (-2);
	}
	return (i);
}

int	tok_one_char(t_token *token, int i, char c, int type)
{
	char	*s;
	char	*tmp;
	t_token	*tmp2;

	tmp = NULL;
	s = token->s;
	if (is_same(s[i], c) && s[i])
	{
		tmp = ft_strndup(&s[i], 1);
		if (!tmp)
			return (-2);
		tmp2 = ft_tokennew(type, tmp);
		if (!tmp2)
			return (ret_int_free(tmp, -2));
		ft_tokenadd_back(&token, tmp2);
		i++;
	}
	return (i);
}

int	lexical_analysis2(t_token *token, int i)
{
	char	*s;

	s = token->s;
	i = tok(token, is_not_incld, T_WORD, i, "\'\"|<>$ \t\n\v\f\r");
	i = tok(token, is_incld, T_PIPE, i, "|");
	i = tok(token, is_incld, T_L_REDIRECT, i, "<");
	i = tok(token, is_incld, T_R_REDIRECT, i, ">");
	i = dq_analysis(token, i);
	i = sq_analysis(token, i);
	i = tok(token, is_incld, T_DOLLAR, i, "$");
	i = tok(token, is_incld, T_SPACE, i, " \t\n\v\f\r");
	if (i == -1 || i == -2)
		return (i);
	while (is_incld(s[i], " \t\n\v\f\r"))
		i++;
	i = tok(token, is_incld, T_SPECIAL, i, "?");
	i = tok(token, is_incld, T_SPACE, i, " \t\n\v\f\r");
	if (i == -1 || i == -2)
		return (i);
	return (i);
}

t_token	*lexical_analysis(char *s, char ***envp)
{
	int		i;
	t_token	*token;

	i = 0;
	token = ft_tokennew(T_START, "T_START");
	if (!token)
	{
		free_token(&token);
		exit(0);
	}
	token->s = s;
	while (s[i])
	{
		i = interate_non_whitespace(token, i, envp);
		if (!i)
			return (NULL);
	}
	if (!s[i])
		ft_tokenadd_back(&token, ft_tokennew(0, T_NULL));
	return (token);
}
