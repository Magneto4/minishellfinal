/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:29:19 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/10/28 10:46:33 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define T_START -1
# define T_NULL 0
# define T_WORD 1
# define T_PIPE 2
# define T_L_REDIRECT 3
# define T_R_REDIRECT 4
# define T_DOUBLE_QUOTES 5
# define T_SINGLE_QUOTES 6
# define T_DOLLAR 7
# define T_SPECIAL 8
# define T_SPACE 9
# define T_SIGINT 100

char	**ft_split_in_two(char *str, char charset);
char	*ft_str_contains(char *str, char *sep);
char	*ft_strndup(char *src, int n);
char	*ft_getenv2(char **envp, char *var);
char	*ft_str_contains_non_alpha(char *str);
char	*ft_create_tmp(char *str);
char	*remove_whitespace(char *str);
void	*null_free(char *str);
void	config_signal(void);
void	config_env(void);
void	run_signals(int sig);
int		is_incld(char c, char *to_find);
int		is_not_incld(char c, char *to_find);
int		is_same(char c, char a);
int		is_word(char c, char a);
int		is_command(char *buf, char *cmd);
int		if_null_fail(char c);
int		delete_tmpfile(char *str);
int		ft_str_contains_only_number(char *str);
int		ret_int_free(char *str, int ret);
int		is_alpha_or_digit_nor_including(char c, char *exclude);
void	*set_global_ret_null(int global);

#endif