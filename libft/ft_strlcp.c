/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:32:52 by hyujung           #+#    #+#             */
/*   Updated: 2022/10/20 16:55:22 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		if (*src)
		{
			*(dest + i) = *src;
			src++;
		}
		else if (!*src)
			*(dest + i) = '\0';
		i++;
	}
	return (dest);
}
