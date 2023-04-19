/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:55:47 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/19 17:42:44 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_struct(t_processes	*info)
{
	if (info->paths)
		free_array(info->paths);
	if (info->pipe_fds)
		free_pipes(info->pipe_fds);
	free(info->ids);
	free(info);
}
