/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:34:43 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/27 16:50:09 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	change_env(char ***envp, char *to_change, char *new)
{
	int		i;
	char	*var;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], to_change, ft_strlen(to_change)) == 0)
			break ;
		i ++;
	}
	if (!(*envp)[i])
		return (MISSING_ENV);
	var = ft_strjoin(to_change, new);
	if (!var)
		return (BAD_MALLOC);
	free ((*envp)[i]);
	(*envp)[i] = var;
	return (0);
}
