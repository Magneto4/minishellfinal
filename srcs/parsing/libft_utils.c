/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:06:00 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/10/27 14:43:27 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_command(char *buf, char *cmd)
{
	char	*buf2;
	char	*cmd2;
	int		ret;

	ret = 1;
	if (!buf || !cmd)
		return (0);
	buf2 = remove_whitespace(buf);
	if (!buf2)
		return (2);
	cmd2 = remove_whitespace(cmd);
	if (!cmd2)
	{
		free(buf2);
		return (2);
	}
	if (!(ft_strnstr(buf2, cmd2, ft_strlen(cmd2))))
		ret = 0;
	if (ft_strlen(buf2) != ft_strlen(cmd2))
		ret = 0;
	if (ft_strlen(buf2))
		free(buf2);
	if (ft_strlen(cmd2))
		free(cmd2);
	return (ret);
}

int	are_words(int num, t_token *token)
{
	while (num)
	{
		if (token->type != T_WORD)
			return (0);
		token = token->next;
		num--;
	}
	return (1);
}

int	is_same(char c, char a)
{
	if (c == a)
		return (1);
	return (0);
}

char	*ft_strndup(char *src, int n)
{
	char	*result;
	int		i;

	i = 0;
	if (!src || !n)
		return (NULL);
	result = (char *)ft_calloc(n + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (i < n)
	{
		result[i] = src[i];
		i++;
	}
	return (result);
}

char	*remove_whitespace(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(str) - 1;
	while (str[i] && is_incld(str[i], "\t\n\v\f\r "))
		i++;
	if (i == (j + 1))
		return ("\0");
	while (str[j] && is_incld(str[j], "\t\n\v\f\r ") && j)
		j--;
	ret = (char *)ft_calloc(sizeof(char), j - i + 2);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, &str[i], j - i + 2);
	return (ret);
}
