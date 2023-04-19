/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:25:40 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/10/28 16:32:11 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_analyse_var(char *var, char *rest)
{
	char	*tmp;

	tmp = NULL;
	if (!var)
	{
		if (rest)
		{
			tmp = ft_strdup(rest);
			if (!tmp)
				exit(BAD_MALLOC);
		}
	}
	if (var && (ft_strlen(var) == 0))
		return (NULL);
	if (var)
	{
		tmp = ft_strjoin(var, rest);
		if (!tmp)
			return (null_free(var));
	}
	return (tmp);
}

char	*ft_search_var(char **split, char **envp)
{
	char	*tmp;
	char	*var;

	tmp = NULL;
	var = ft_getenv2(envp, split[0]);
	tmp = ft_analyse_var(var, split[1]);
	free (var);
	if (!tmp)
		return (NULL);
	if (!split[0])
	{
		var = ft_strjoin("$", tmp);
		if (!var)
			return (null_free(tmp));
		if (split[1])
			free(tmp);
		tmp = var;
	}
	return (tmp);
}

char	*ft_split_and_join(t_token *t, char **envp, char c)
{
	char	*tmp;
	char	**split;

	tmp = NULL;
	split = ft_split_in_two(t->str, c);
	if (!split)
		ft_free_and_exit(t, envp);
	tmp = ft_search_var(split, envp);
	free(split[0]);
	free(split[1]);
	free(split);
	if (!tmp)
		ft_free_and_exit(t, envp);
	return (tmp);
}

char	*ft_check_if_env_split(t_token *t, char **envp)
{
	char	*tmp;
	char	*sep;
	char	*tmp2;

	tmp2 = NULL;
	sep = ft_str_contains_non_alpha(t->str);
	if (sep)
		tmp = ft_split_and_join(t, envp, *sep);
	else
	{
		tmp = ft_getenv2(envp, t->str);
		if (!tmp)
			return (NULL);
		if (ft_strlen(tmp) == 0)
			ft_free_and_exit(t, envp);
		if (ft_str_contains(tmp, " \t\n\v\f\r"))
		{
			tmp2 = remove_whitespace(tmp);
			free(tmp);
			if (!tmp2)
				ft_free_and_exit(t, envp);
			tmp = tmp2;
		}
	}
	return (tmp);
}

int	ft_insert_special_token(t_token *t, int i)
{
	char	*special;
	t_token	*tmp2;

	tmp2 = NULL;
	special = (char *)ft_calloc(sizeof(char), (i + 1));
	if (!special)
		return (0);
	tmp2 = ft_tokennew(T_WORD, ft_memset(special, '?', i));
	if (!tmp2)
		return (ret_int_free(special, 0));
	ft_token_insert(&t, tmp2);
	return (1);
}
