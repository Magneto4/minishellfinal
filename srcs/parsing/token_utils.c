/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:57:29 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/10/28 15:35:35 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*ft_tokenlast(t_token *t)
{
	if (t != NULL)
	{
		while (t->next)
			t = t->next;
	}
	return (t);
}

void	ft_tokenadd_back(t_token **t, t_token *new)
{
	t_token	*tmp;

	tmp = NULL;
	if (!(t && new))
		return ;
	if (!*t)
		*t = new;
	else
	{
		tmp = ft_tokenlast(*t);
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
}

t_token	*ft_tokennew(int type, char *str)
{
	t_token	*result;

	result = malloc(sizeof(t_token));
	if (!result)
		return (NULL);
	result->type = type;
	result->i = 0;
	result->str = str;
	result->prev = NULL;
	result->next = NULL;
	return (result);
}

void	ft_token_remove_and_connect(t_token **t)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp2 = (*t)->prev;
	tmp = (*t)->next;
	free((*t)->str);
	free((*t));
	(*t) = tmp;
	tmp2->next = (*t);
	(*t)->prev = tmp2;
}

void	ft_token_insert(t_token **t, t_token *new)
{
	t_token	*tmp;

	tmp = (*t)->next;
	(*t)->next = new;
	new->next = tmp;
	new->prev = (*t);
	tmp->prev = new;
	return ;
}
