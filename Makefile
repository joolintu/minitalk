# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlintune <jlintune@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/26 19:39:43 by jlintune          #+#    #+#              #
#    Updated: 2023/07/31 21:32:36 by jlintune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = both

CFLAGS =-Wall -Werror -Wextra
LIB_DIR	= $(CURDIR)/Libft
LIBRARY = $(LIB_DIR)/libft.a
LIBFLAGS = -L$(LIB_DIR) -lft

SERVER_TARGET = server
CLIENT_TARGET = client

SERVER_SRCS = server.c server_parsers.c server_handlers.c
CLIENT_SRCS = client.c client_senders.c

SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS	= $(CLIENT_SRCS:.c=.o)


all: $(NAME)
#This is silly, target NAME should not be required for this project

$(NAME): $(LIBRARY) $(SERVER_TARGET) $(CLIENT_TARGET)

$(SERVER_TARGET): $(LIBRARY) $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(LIBFLAGS) -o $@ $^

$(CLIENT_TARGET): $(LIBRARY) $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(LIBFLAGS) -o $@ $^

$(LIBRARY):
	$(MAKE) -C $(LIB_DIR)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIB_DIR) clean
	/bin/rm -f $(SERVER_OBJS) $(CLIENT_OBJS)

fclean: clean
	$(MAKE) -C $(LIB_DIR) fclean
	/bin/rm -f $(SERVER_TARGET) $(CLIENT_TARGET)

re: fclean all

bonus:

.PHONY: all both test clean fclean re bonus