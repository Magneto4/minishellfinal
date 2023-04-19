/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 19:47:03 by hyujung           #+#    #+#             */
/*   Updated: 2022/07/22 13:23:30 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strchr(const char *str, int i)
{
	char	*ptr;

	ptr = (char *) str;
	while (*ptr != (char)i && ptr)
	{
		if (*ptr == '\0')
			return (NULL);
		ptr++;
	}
	return (&(*ptr));
}
