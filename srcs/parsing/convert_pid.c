/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_pid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:24:08 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/10/28 17:48:27 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_return_pid(t_token *t, int i)
{
	char	*ret;
	char	*dollar;
	t_token	*dol_tok;

	ret = ft_calloc(i, sizeof(char));
	if (!ret)
		return (NULL);
	dollar = ft_calloc(2, sizeof(char));
	if (!dollar)
		return (free(ret), NULL);
	ft_memset(ret, '$', i - 1);
	ft_memset(dollar, '$', 1);
	dol_tok = ft_tokennew(T_DOLLAR, dollar);
	if (!dol_tok)
		return (free(ret), free(dollar), NULL);
	ft_token_insert(&t, dol_tok);
	dol_tok = ft_tokennew(T_WORD, ret);
	if (!dol_tok)
		return (free(ret), free(dollar), NULL);
	ft_token_insert(&t, dol_tok);
	return (ret);
}

t_token	*ft_convert_to_pid(t_token *t)
{
	int		i;
	char	*ret;

	ret = NULL;
	i = ft_strlen(t->str);
	if (i < 2)
		return (t);
	ret = ft_return_pid(t, i);
	if (!ret)
		return (NULL);
	ft_token_remove_and_connect(&t);
	return (t);
}
