/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahjung <hyunahjung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:32:52 by hyujung           #+#    #+#             */
/*   Updated: 2022/09/14 17:00:13 by hyunahjung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	offset;
	unsigned int	len;

	offset = 0;
	if (!dstsize)
		return (ft_strlen(src));
	len = ft_strlen(src);
	if (dstsize > 0)
	{
		while (*(src + offset) != '\0' && offset < dstsize - 1)
		{
			*(dst + offset) = *(src + offset);
			offset++;
		}
	}
	*(dst + offset) = '\0';
	while (*(src + offset) != '\0')
		offset++;
	return (len);
}
