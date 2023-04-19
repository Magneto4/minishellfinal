# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/02 13:35:31 by nseniak           #+#    #+#              #
#    Updated: 2022/10/21 16:24:39 by hyujung          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ft_isalpha.c ft_memchr.c ft_putchar_fd.c ft_strchr.c ft_strlcpy.c\
 ft_strrchr.c ft_atoi.c ft_isascii.c ft_memcmp.c ft_putendl_fd.c\
 ft_strdup.c ft_strlen.c ft_strtrim.c ft_bzero.c ft_isdigit.c ft_memcpy.c\
 ft_putnbr_fd.c ft_striteri.c ft_strmapi.c ft_substr.c ft_isalnum.c ft_itoa.c\
 ft_memset.c ft_split.c ft_strlcat.c ft_strnstr.c ft_toupper.c ft_calloc.c\
 ft_isprint.c ft_memmove.c ft_putstr_fd.c ft_strjoin.c ft_strncmp.c ft_tolower.c
OBJS		= ${SRCS:.c=.o}
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
NAME		= libft.a
BONUS		= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
 ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJS_BONUS	= ${BONUS:.c=.o}

%.o: %.c ${SRCS}
		$(CC) $(FLAGS) -c -o $@ $< 

$(NAME): ${OBJS}
		ar rcs ${NAME} ${OBJS}

all: $(NAME)

bonus: ${OBJS} ${OBJS_BONUS}
		ar rcs ${NAME} ${OBJS} ${OBJS_BONUS}

clean:
		rm -f ${OBJS} ${OBJS_BONUS}

fclean:	clean
		rm -f ${NAME}

re:		fclean all

.PHONY:	all clean fclean re
