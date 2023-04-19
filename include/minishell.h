/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseniak <nseniak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:52:37 by hyunahjung        #+#    #+#             */
/*   Updated: 2022/10/28 17:34:04 by nseniak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "cmd_exec.h"
# include "builtins.h"
# include "parsing.h"
# include <errno.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>

typedef struct s_token{
	int				type;
	int				i;
	char			*str;
	struct s_token	*prev;
	struct s_token	*next;
	char			*s;
}	t_token;

typedef struct s_command{
	char	*name;
	t_list	*param;
	void	*func;
}	t_command;

typedef struct s_processes
{
	int		number_of_pipes;
	int		number_of_child;
	char	***envp;
	char	**paths;
	int		**pipe_fds;
	int		*ids;
	t_token	*token;
}				t_processes;

int			execution(t_token *token, char ***envp);

t_token		*lexical_analysis(char *s, char ***envp);
t_token		*heredoc_lexical_analysis(char *s);
t_token		*ft_tokenlast(t_token *t);
t_token		*check_heredoc(t_token *token, char **envp);
t_token		*word_expension(t_token *token, char **envp);
t_token		*ft_convert_to_pid(t_token *t);
t_token		*ft_fail(void);
t_token		*syntax_pipeline(t_token *token);
t_token		*ft_tokennew(int type, char *str);
t_token		*ft_tokenlast(t_token *t);
t_token		*syntax_simple_cmd(t_token *token);
t_token		*syntax_io_redirect(t_token *token);
t_token		*syntax_check_pipeline(t_token *token);
char		*ft_check_if_env_split(t_token *t, char **envp);
char		*check_if_start_by_num(t_token *t);
void		ft_token_insert(t_token **t, t_token *new);
void		free_and_exit(t_token *t, char **envp);
void		ft_token_remove_and_connect(t_token **t);
void		ft_tokenadd_back(t_token **t, t_token *new);
void		ft_token_remove_and_connect(t_token **t);
void		free_token(t_token **t);
void		ft_modify_token_with_env(t_token *t, char *tmp);
void		free_token(t_token **t);
int			ft_sq_lexical_analysis(t_token *token, int i);
int			remove_space_token(t_token *t);
int			dollar_before_quote(t_token *token);
int			merge_word(t_token *t);
int			syntax_analysis(t_token *t, char **envp);
int			tok(t_token *t, int (*f)(char, char*), int tt, int i, char *a);
int			interate_non_whitespace(t_token *token, int i, char ***envp);
int			prepare_builtin(t_token *token, t_processes *info);
int			dq_analysis(t_token *token, int i);
int			sq_analysis(t_token *token, int i);
int			tok_one_char(t_token *token, int i, char c, int type);
int			are_words(int num, t_token *token);
int			write_token2file(t_token *heredoc_token, int fd);
void		*null_free_tok(t_token *t);
void		ft_free_and_exit(t_token *t, char **envp);
int			ft_insert_special_token(t_token *t, int i);
int			lexical_analysis2(t_token *token, int i);
int			check_endcmd(t_token *token, char *buf, int fd);
void		*token_operation(t_token *hd, char **envp, int fd, char *buf);
void		change_everything_to_word(t_token *token);

char		**get_argv(t_token *token);

int			no_fork(t_token *token);

int			redirections(t_token *token);

void		free_struct(t_processes	*info);

int			handle_pipes(t_processes *info, int i);

int			create_pipes(t_processes *info);

int			exec_builtin(char **argv, t_processes *info);

int			export(char **argv, t_processes *info);

int			unset(char **argv, t_processes *info);

int			forks(t_processes *info, t_token *token);

int			child_process(t_token *token, t_processes *info, int i);

t_processes	*init_info(t_token *token, char ***envp);

void		close_pipes(t_processes *info);

void		bad_fork_exit(t_token *t, char *filename, char **envp);

#endif
