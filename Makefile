NAME		= 	minishell

SRCS		=	srcs/main.c \
				srcs/parsing/heredoc.c \
				srcs/parsing/heredoc2.c \
				srcs/parsing/config_signal.c \
				srcs/parsing/lexical.c \
				srcs/parsing/syntax.c \
				srcs/parsing/syntax_utils.c \
				srcs/parsing/convert_pid.c \
				srcs/parsing/free_func.c \
				srcs/parsing/grammar.c \
				srcs/parsing/grammar2.c \
				srcs/parsing/libft_utils.c \
				srcs/parsing/rm_useless_t.c \
				srcs/parsing/lexical_heredoc.c \
				srcs/parsing/export_errors.c \
				srcs/parsing/str_contains.c \
				srcs/parsing/quote.c \
				srcs/parsing/quote_utils.c \
				srcs/parsing/utils.c \
				srcs/parsing/token_utils.c \
				srcs/parsing/word_expansion.c \
				srcs/parsing/word_expansion2.c \
				srcs/cmd_exec/prepare_exec.c \
				srcs/cmd_exec/child_exec.c \
				srcs/cmd_exec/pipes.c \
				srcs/cmd_exec/get_cmd.c \
				srcs/cmd_exec/array_func.c \
				srcs/builtins/echo.c \
				srcs/builtins/pwd.c \
				srcs/builtins/cd.c \
				srcs/builtins/ft_getenv.c \
				srcs/builtins/change_env.c \
				srcs/builtins/exec_builtin.c \
				srcs/builtins/env.c \
				srcs/builtins/export.c \
				srcs/builtins/unset.c \
				srcs/cmd_exec/free_struct.c \
				srcs/cmd_exec/redirections.c \
				srcs/cmd_exec/info_init.c \
				srcs/builtins/exit.c \

OBJS		=	${SRCS:.c=.o}

CC			=	cc

CFLAG		= -Wextra -Werror -Wall

%.o: %.c ${SRCS}
		$(CC) $(CFLAG) -c -o $@ $< 

${NAME}:	${OBJS}
			make -C libft all
			${CC} -o $(NAME) ${OBJS} -L./libft -lft -lreadline

all:		${NAME}

clean:
			make -C libft clean
			rm	-f ${OBJS}

fclean:		clean
			make -C libft fclean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re