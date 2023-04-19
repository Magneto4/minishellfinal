/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:02:49 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/10/28 09:36:38 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_and_exit(t_token *t, char **envp)
{
	while (t->type != T_START)
		t = t->prev;
	free_token(&t);
	free_array(envp);
	exit(BAD_MALLOC);
}

void	*null_free(char *str)
{
	free(str);
	return (NULL);
}

int	ret_int_free(char *str, int ret)
{
	free(str);
	return (ret);
}

void	*null_free_tok(t_token *t)
{
	free_token(&t);
	return (NULL);
}

void	free_and_exit(t_token *t, char **envp)
{
	free_token(&t);
	free_array(envp);
	exit(BAD_MALLOC);
}
