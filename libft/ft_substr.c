/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahjung <hyunahjung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 21:23:10 by hyujung           #+#    #+#             */
/*   Updated: 2022/09/14 17:00:45 by hyunahjung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if (!len || (ft_strlen(s) <= start))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i] && (j < len))
	{
		if (i >= start)
			result[j++] = s[i];
	}
	result[j] = 0;
	return (result);
}
