/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:12:47 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/28 15:39:47 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(void)
{
	char	*pwd;
	int		ret;

	ret = get_new_dir(&pwd);
	if (ret)
	{
		write(STDERR_FILENO, "pwd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory\n", 110);
		return (1);
	}
	printf("%s\n", pwd);
	free (pwd);
	return (0);
}
