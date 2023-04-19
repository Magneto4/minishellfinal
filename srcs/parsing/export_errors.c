/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:40:47 by hyujung           #+#    #+#             */
/*   Updated: 2022/10/28 15:35:11 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_iterate_til_new_filename(char *str, char *filename)
{
	char	*cpt_str;
	int		cpt;

	cpt = 0;
	while (access(filename, F_OK) == 0)
	{
		free(filename);
		cpt++;
		cpt_str = ft_itoa(cpt);
		if (!cpt_str)
			return (NULL);
		filename = ft_strjoin(str, cpt_str);
		free(cpt_str);
		if (!filename)
			return (null_free(cpt_str));
	}
	return (filename);
}

char	*ft_create_tmp(char *str)
{
	char	*filename;
	int		cpt;
	char	*cpt_str;

	cpt = 0;
	cpt_str = ft_itoa(cpt);
	if (!cpt_str)
		return (NULL);
	filename = ft_strjoin(str, cpt_str);
	if (!filename)
		return (null_free(cpt_str));
	filename = ft_iterate_til_new_filename(str, filename);
	if (!filename)
		return (null_free(cpt_str));
	free(cpt_str);
	return (filename);
}

int	ft_iterate_and_delete(char *filename, char *str)
{
	int		cpt;
	char	*num;

	cpt = 0;
	while (access(filename, F_OK) == 0)
	{
		unlink(filename);
		free(filename);
		cpt++;
		num = ft_itoa(cpt);
		if (!num)
			return (1);
		filename = ft_strjoin(str, num);
		free(num);
		if (!filename)
			return (1);
	}
	free(filename);
	return (0);
}

int	delete_tmpfile(char *str)
{
	int		cpt;
	char	*num;
	char	*filename;

	cpt = 0;
	num = ft_itoa(cpt);
	if (!num)
		return (1);
	filename = ft_strjoin(str, num);
	free(num);
	if (!filename)
		return (1);
	if (ft_iterate_and_delete(filename, str) == 1)
		return (1);
	return (0);
}

int	merge_word(t_token *t)
{
	char	*new;

	new = NULL;
	t = t->next;
	while (t && t->type != T_NULL)
	{
		if (are_words(2, t))
		{
			new = ft_strjoin(t->str, t->next->str);
			if (!new)
				return (2);
			ft_token_remove_and_connect(&t);
			free(t->str);
			t->str = new;
		}
		else
			t = t->next;
	}
	return (0);
}
