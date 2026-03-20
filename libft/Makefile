# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aronnet <aronnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/14 11:03:54 by aronnet           #+#    #+#              #
#    Updated: 2026/02/13 01:47:32 by aronnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SOURCES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
          ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
          ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
          ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
          ft_strlcat.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
          ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
          ft_strlcpy.c ft_strjoin.c

BONUS_SOURCES = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstdelone_bonus.c ft_lstlast_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
                ft_lstmap_bonus.c

OBJECTS = $(SOURCES:.c=.o)
BONUS_OBJECTS = $(BONUS_SOURCES:.c=.o)

OBJECTS = $(SOURCES:.c=.o)
CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs
RM = rm -f
CC = cc

all: $(NAME)
$(NAME): $(OBJECTS)
	$(AR) $(NAME) $(OBJECTS)
%.o: %.c libft.h
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	$(RM) $(OBJECTS)
fclean: clean
	$(RM) $(NAME)
re: fclean all

bonus: $(OBJECTS) $(BONUS_OBJECTS)
	$(AR) $(NAME) $(OBJECTS) $(BONUS_OBJECTS)

.PHONY: all clean fclean re