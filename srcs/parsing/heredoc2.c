/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:10:13 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/28 15:31:16 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	bad_fork_exit(t_token *t, char *filename, char **envp)
{
	free_token(&t);
	free_array(envp);
	free(filename);
	exit(FAILED_FORK);
}
