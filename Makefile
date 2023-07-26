# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlintune <jlintune@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/26 19:39:43 by jlintune          #+#    #+#              #
#    Updated: 2023/07/26 21:16:13 by jlintune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = both

CFLAGS =#-Wall -Werror -Wextra
LIBDIR	= $(CURDIR)/Libft
LIBRARY = $(LIBDIR)/libft.a

SERVER_TARGET = server
CLIENT_TARGET = client
TEST_SERVER = test_$(SERVER_TARGET)
TEST_CLIENT = test_$(CLIENT_TARGET)

SERVER_SRCS = server.c #minitalk_utils.c
CLIENT_SRCS = client.c #minitalk_utils.c

SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS	= $(CLIENT_SRCS:.c=.o)


all: $(NAME)
#This is silly, target NAME should not be required for this project

$(NAME): $(SERVER_TARGET) $(CLIENT_TARGET)

test: $(TEST_SERVER) $(TEST_CLIENT)

$(TEST_SERVER): test_$(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_CLIENT): test_$(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(SERVER_TARGET): $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT_TARGET): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^


%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	/bin/rm -f $(SERVER_OBJS) $(CLIENT_OBJS) test_$(SERVER_OBJS) test_$(CLIENT_OBJS)

fclean: clean
	/bin/rm -f $(SERVER_TARGET) $(CLIENT_TARGET) test_$(SERVER_TARGET) test_$(CLIENT_TARGET)

re: fclean all

bonus:

.PHONY: all both test clean fclean re bonus