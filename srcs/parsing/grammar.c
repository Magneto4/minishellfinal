/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:03:31 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/10/28 17:04:39 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*syntax_redirects(t_token *token)
{
	if (token && (token->type == T_L_REDIRECT || token->type == T_R_REDIRECT))
		token = syntax_io_redirect(token);
	if (token && token->type == T_NULL)
		return (ft_fail());
	if (token && token->type != T_WORD)
		return (ft_fail());
	while (token && token->type == T_WORD)
		token = token->next;
	if (token && (token->type == T_L_REDIRECT || token->type == T_R_REDIRECT))
		token = syntax_redirects(token);
	if (token == NULL)
		return (NULL);
	return (token);
}

t_token	*syntax_cmd(t_token *token)
{
	while (token && token->type == T_WORD)
		token = syntax_simple_cmd(token);
	if (token && (token->type == T_L_REDIRECT || token->type == T_R_REDIRECT))
		token = syntax_redirects(token);
	if (token && token->type == T_PIPE)
	{
		token = syntax_check_pipeline(token);
		if (!token)
			return (NULL);
		token = syntax_pipeline(token->next);
	}
	if (token && token->type == T_NULL)
		return (token);
	if (token == NULL)
		return (NULL);
	return (ft_fail());
}

t_token	*syntax_pipeline(t_token *token)
{
	if (token == NULL)
		return (NULL);
	if (token && (token->type == T_PIPE || token->type == T_NULL))
		return (ft_fail());
	if (token && (token->type == T_L_REDIRECT || token->type == T_R_REDIRECT))
		token = syntax_redirects(token);
	while (token && token->type == T_WORD)
		token = syntax_cmd(token);
	if (token && (token->type == T_L_REDIRECT || token->type == T_R_REDIRECT))
		token = syntax_redirects(token);
	if (token && token->type == T_PIPE)
	{
		token = syntax_check_pipeline(token);
		if (token == NULL)
			return (NULL);
		token = syntax_pipeline(token->next);
	}
	if (token && token->type == T_NULL)
		return (token);
	if (token == NULL)
		return (NULL);
	return (ft_fail());
}

void	change_everything_to_word(t_token *token)
{
	t_token	*t;

	t = token;
	while (t && t->type != T_NULL)
	{
		while (t->type != T_SPACE && t->type != T_NULL)
		{
			t->type = T_WORD;
			t = t->next;
		}
		t = t->next;
	}
	merge_word(token);
}
