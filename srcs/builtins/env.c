/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:46:21 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/19 16:33:34 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env(char **argv, char **envp)
{
	if (argv[1])
		return (TOO_MANY_ARGS);
	while (*envp)
	{
		printf("%s\n", *envp);
		envp ++;
	}
	return (0);
}
