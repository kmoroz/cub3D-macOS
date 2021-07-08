# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ksmorozo <ksmorozo@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/10 19:37:56 by ksmorozo      #+#    #+#                  #
#    Updated: 2021/07/08 16:16:09 by ksmorozo      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC_FILES = ft_isdigit.c ft_isspace.c \
ft_memset.c ft_isalpha.c \
ft_strdup.c ft_lstnew.c \
ft_itoa.c ft_strchr.c \
ft_strnstr.c ft_strncmp.c \
ft_isalnum.c ft_strlcpy.c \
ft_strlen.c ft_strtrim.c

HEADER_FILES = libft.h
CFLAGS = -g -Wall -Wextra -Werror
OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rc $@ $^
	ranlib $@

%.o: %.c $(HEADER_FILES)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
