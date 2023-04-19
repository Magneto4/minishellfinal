/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:30:56 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/10/28 15:37:24 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_ret;

int	ft_next_special(t_token *t)
{
	char	*tmp;
	int		i;

	if (t->type == T_SPECIAL)
	{
		i = ft_strlen(t->str);
		tmp = ft_itoa(g_ret);
		if (!tmp)
			return (0);
		free(t->str);
		t->str = tmp;
		t->type = T_WORD;
		i--;
		if (i)
		{
			if (!ft_insert_special_token(t, i))
				return (0);
		}
	}
	return (1);
}

int	ft_next_type_analysis2(t_token *t, char *tmp)
{
	ft_modify_token_with_env(t, tmp);
	return (1);
}

t_token	*ft_next_type_analysis(t_token *t, char **envp)
{
	char	*tmp;
	int		i;

	i = 1;
	if (t->type == T_WORD)
	{
		tmp = ft_check_if_env_split(t, envp);
		if (!tmp)
		{
			tmp = check_if_start_by_num(t);
			if (!tmp)
				return (NULL);
			ft_token_remove_and_connect(&t);
			return (t->prev);
		}
		else
			i = ft_next_type_analysis2(t, tmp);
	}
	else if (t->type == T_SPECIAL)
		i = ft_next_special(t);
	if (!i)
		return (NULL);
	return (t);
}

t_token	*check_env_and_modify_token(t_token *token, char **envp)
{
	t_token	*t;

	t = token;
	if (t->type != T_DOLLAR)
		return (token);
	t = ft_convert_to_pid(t);
	if (!t)
		return (NULL);
	if (t->type != T_DOLLAR)
		return (t);
	if (ft_strlen(t->str) == 1 && (t->next->type == 0 || t->next->type == 9))
	{
		t->type = T_WORD;
		return (t);
	}
	t = t->next;
	if (t->type == T_DOLLAR || t->type == T_WORD || t->type == T_SPECIAL)
		ft_token_remove_and_connect(&(t->prev));
	return (ft_next_type_analysis(t, envp));
}

t_token	*word_expension(t_token *token, char **envp)
{
	t_token	*t;

	t = token;
	while (t && t->type != T_NULL)
	{
		t = check_env_and_modify_token(t, envp);
		if (!t)
			return (NULL);
		t = t->next;
	}
	return (token);
}
