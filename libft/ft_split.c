/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 22:24:54 by hyujung           #+#    #+#             */
/*   Updated: 2022/07/22 13:23:34 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	count(const char *str, char charset)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (str[i] && str[i] == charset)
		i++;
	while (str[i])
	{
		counter++;
		while (str[i] != charset && str[i])
			i++;
		while (str[i] == charset && str[i])
			i++;
	}
	return (counter);
}

static char	*ft_strdup2(int start, int end, const char *str)
{
	char	*s;
	int		i;
	int		j;

	s = (char *)malloc(sizeof(char) * ((end - start) + 1));
	i = start;
	j = 0;
	if (!s)
		return (NULL);
	while (str[i] && (i < end))
	{
		s[j] = (char)str[i];
		i++;
		j++;
	}
	s[j] = '\0';
	return (s);
}

char	**ft_split(const char *str, char charset)
{
	char	**tab;
	int		start;
	int		i;
	int		cpt;

	if (!str)
		return (NULL);
	tab = (char **)malloc (sizeof(char *) * (count(str, charset) + 1));
	if (!(tab))
		return (NULL);
	i = 0;
	cpt = 0;
	while (str[i] && (count(str, charset) > cpt))
	{
		while (str[i] == charset && str[i])
			i++;
		start = i;
		while (str[i] != charset && str[i])
			i++;
		tab[cpt] = ft_strdup2(start, i, str);
		cpt++;
	}
	tab[cpt] = 0;
	return (tab);
}
