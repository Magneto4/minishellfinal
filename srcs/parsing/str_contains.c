/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_contains.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:43:19 by hyujung           #+#    #+#             */
/*   Updated: 2022/10/25 12:53:38 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_str_contains_non_alpha(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (&str[i]);
	}
	return (NULL);
}

int	ft_str_contains_only_number(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}	
	return (1);
}

char	*ft_str_contains(char *str, char *sep)
{
	int		i;
	char	*ret;

	ret = NULL;
	i = -1;
	while (sep[++i])
	{
		ret = ft_strchr(str, sep[i]);
		if (ret)
			return (ret);
	}
	return (ret);
}

int	is_incld(char c, char *to_find)
{
	int	i;

	i = -1;
	if (!to_find || !c)
		return (0);
	while (to_find[++i])
	{
		if (c == to_find[i])
			return (1);
	}
	return (0);
}

int	is_not_incld(char c, char *to_find)
{
	int	i;

	i = -1;
	if (!to_find || !c)
		return (0);
	while (to_find[++i])
	{
		if (c == to_find[i])
			return (0);
	}
	return (1);
}
