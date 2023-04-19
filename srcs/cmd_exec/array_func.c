/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:51:51 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/27 16:46:19 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	array_length(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i ++;
	return (i);
}

char	**array_append(char **array, char *str)
{
	char	**temp;
	int		n;
	int		i;

	n = 0;
	while (array[n])
		n ++;
	temp = malloc((n + 2) * sizeof(*temp));
	if (!temp)
		return (NULL);
	i = -1;
	while (++i <= n)
	{
		if (i < n)
			temp[i] = ft_strdup(array[i]);
		else
			temp[i] = ft_strdup(str);
		if (!temp[i])
		{
			free_array(temp);
			return (NULL);
		}
	}
	temp[i] = NULL;
	return (temp);
}

int	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i ++;
	}
	free (array);
	return (0);
}

char	**array_dup(char **src)
{
	int		i;
	char	**dest;

	dest = malloc ((array_length(src) + 1) * sizeof(*dest));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < array_length(src))
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
		{
			while (i--)
				free (dest[i]);
			free (dest);
			return (NULL);
		}
		i ++;
	}
	dest[i] = NULL;
	return (dest);
}
