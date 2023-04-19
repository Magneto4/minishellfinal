/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahjung <hyunahjung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:04:58 by hyujung           #+#    #+#             */
/*   Updated: 2022/09/14 17:00:22 by hyunahjung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			(**ptr)(unsigned int, char);
	char			*result;
	unsigned int	i;

	ptr = &f;
	i = 0;
	if (!s || !f)
		return (NULL);
	result = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	while (s[i])
	{
		result[i] = (*ptr)(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
