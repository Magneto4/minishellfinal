/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:05:36 by nseniak           #+#    #+#             */
/*   Updated: 2022/10/28 15:39:35 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	echo(char **argv);

int	pwd(void);

int	ft_getenv(char **envp, char *var, char **res);

int	change_env(char ***envp, char *to_change, char *new);

int	cd(char ***envp, char **argv);

int	env(char **argv, char **envp);

int	is_builtin(char *cmd);

int	ft_exit(char **argv);

int	get_new_dir(char **pwd);

#endif