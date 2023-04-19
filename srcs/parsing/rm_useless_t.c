/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_useless_t.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:07:21 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/10/28 16:47:29 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_ret;

int	if_null_fail(char c)
{
	if (!c)
	{
		g_ret = SYNTAX_ERROR;
		ft_fail();
		return (1);
	}
	return (0);
}

t_token	*convert_special(t_token *t)
{
	char	*new;

	if (t->next->type == T_WORD)
	{
		new = ft_strjoin(t->str, t->next->str);
		if (!new)
			return (NULL);
		free(t->next->str);
		t->next->str = new;
		ft_token_remove_and_connect(&t);
	}
	else
		t->type = T_WORD;
	return (t);
}

int	remove_space_token(t_token *t)
{
	while (t && t->type != T_NULL)
	{
		if (t->type == T_DOLLAR)
		{
			t->type = T_WORD;
			t = t->next;
		}
		else if (t->type == T_SPECIAL)
		{
			t = convert_special(t);
			if (!t)
				return (2);
		}
		else if (t->type == T_SPACE)
			ft_token_remove_and_connect(&t);
		else
			t = t->next;
	}
	return (0);
}
