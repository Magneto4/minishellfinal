/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:53:01 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/28 22:03:21 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_EXEC_H
# define CMD_EXEC_H

# include "minishell.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# define TOO_MANY_ARGS 1
# define MISSING_ENV 5
# define BAD_MALLOC 6
# define FAILED_FORK 7
# define FAILED_PIPE 8
# define EXIT 9
# define FAILED_DUP 10
# define FAILED_OPEN 14
# define CMD_NOT_FOUND 127
# define FAILED_FUN 15
# define MISSING_FILE 16
# define SYNTAX_ERROR 2
# define PERMISSION_DENIED 1
# define IN_HEREDOC 999
# define DONT_IGNORE 998

int		give_cmd_with_path(char *cmd_name, char **paths, char **cmd);

char	**array_append(char **array, char *str);

int		free_array(char **array);

int		array_length(char **array);

char	**array_dup(char **src);

void	free_pipes(int **pipe_fds);

void	print_error(int error);

#endif