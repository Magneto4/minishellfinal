/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:44:55 by hyujung           #+#    #+#             */
/*   Updated: 2022/10/28 20:15:24 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*syntax_simple_cmd(t_token *token)
{
	if (token->type == T_WORD)
		return (token->next);
	else
		return (ft_fail());
}

t_token	*syntax_io_redirect(t_token *token)
{
	if ((token->type == T_L_REDIRECT || token->type == T_R_REDIRECT))
	{
		if (ft_strlen(token->str) > 2)
			return (ft_fail());
		return (token->next);
	}
	return (ft_fail());
}

t_token	*syntax_check_pipeline(t_token *token)
{
	if (token && ft_strlen(token->str) > 1)
		return (ft_fail());
	return (token);
}
