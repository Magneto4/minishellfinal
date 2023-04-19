/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahjung <hyunahjung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 19:47:47 by hyujung           #+#    #+#             */
/*   Updated: 2022/09/14 17:00:37 by hyunahjung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *str, int j)
{
	int	len;

	len = ft_strlen(str);
	while (0 <= len)
	{
		if (str[len] == (char)j)
			return (&(((char *)str)[len]));
		len--;
	}
	return (NULL);
}
