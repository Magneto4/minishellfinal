/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:14:32 by hyujung           #+#    #+#             */
/*   Updated: 2022/10/28 10:48:15 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_dollar(t_token *before_qt, int len)
{
	char	*new;

	new = NULL;
	if (len == 1)
	{
		before_qt->prev->next = NULL;
		free(before_qt->str);
		free(before_qt);
	}
	else if (len % 2 == 1)
	{
		new = ft_calloc(len, sizeof(char));
		if (!new)
			return (0);
		free(before_qt->str);
		ft_memset(new, '$', len - 1);
		before_qt->str = new;
	}
	return (1);
}

int	dollar_before_quote(t_token *token)
{
	int		len;
	t_token	*before_qt;

	before_qt = ft_tokenlast(token);
	if (before_qt->type == T_DOLLAR)
	{
		len = ft_strlen(before_qt->str);
		if (!add_dollar(before_qt, len))
			return (0);
	}
	return (1);
}

int	ft_sq_lexical_analysis(t_token *token, int i)
{
	t_token	*tmp;
	char	*tmp2;
	char	*s;

	tmp = NULL;
	tmp2 = NULL;
	s = token->s;
	if (is_same(s[i], 39))
	{
		tmp2 = ft_strdup("\0");
		if (!tmp2)
			return (-2);
		tmp = ft_tokennew(T_WORD, tmp2);
		if (!tmp)
			return (ret_int_free(tmp2, -2));
		ft_tokenadd_back(&token, tmp);
	}
	if (ft_tokenlast(token)->type == T_DOLLAR)
	{
		if (!dollar_before_quote(token))
			return (-2);
	}
	return (0);
}

char	**ft_split_in_two(char *str, char charset)
{
	char	**result;
	int		i;
	int		start;

	i = 0;
	while (str[i] && (str[i] != charset))
		i++;
	result = (char **)ft_calloc(2, sizeof(char *));
	if (!(result))
		return (NULL);
	result[0] = ft_strndup(&str[0], i);
	start = i;
	result[1] = ft_strndup(&str[start], ft_strlen(&str[start]));
	return (result);
}

void	*token_operation(t_token *heredoc_token, char **envp, int fd, char *buf)
{
	t_token	*tmp;

	tmp = word_expension(heredoc_token, envp);
	if (!tmp)
		return (NULL);
	write_token2file(heredoc_token, fd);
	free_token(&heredoc_token);
	free(buf);
	return (tmp);
}
