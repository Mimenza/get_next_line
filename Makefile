# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 10:55:33 by emimenza          #+#    #+#              #
#    Updated: 2023/10/05 10:55:35 by emimenza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB			=	ar rcs
DEL			=	rm -f
CC			=	gcc
CCFLAGS		=	-Wall -Wextra -Werror
NAME		=	get_next_line.a
SRC			=	get_next_line.c get_next_line_utils.c

OBJ			=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME):$(OBJ)
		$(LIB) $(NAME) $(OBJ)
# $@ : The file name of the target of the rule. If the target is an archive member, then ‘$@’ is the name of the archive file.
# $< : The name of the first prerequisite.

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<
	
clean:
	$(DEL) $(OBJ)
	
fclean: clean
	$(DEL) $(NAME)
re:	fclean all