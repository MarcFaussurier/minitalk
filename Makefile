# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafaussu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 13:27:28 by mafaussu          #+#    #+#              #
#    Updated: 2022/05/13 15:18:32 by mafaussu         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CLIENT=client
SERVER=server
CFLAGS=-Wall -Werror -Wextra #-g
DEPS=minitalk.h Makefile

all: $(CLIENT) $(SERVER)

minitalk.o:	minitalk.c $(DEPS)
	cc $(CFLAGS) -c minitalk.c -o minitalk.o

$(CLIENT):	minitalk.o client.c $(DEPS)
	cc $(CFLAGS) client.c minitalk.o -o $(CLIENT)

$(SERVER):	minitalk.o server.c $(DEPS)
	cc $(CFLAGS) server.c minitalk.o -o $(SERVER)

clean:
	rm -rf minitalk.o

fclean:	clean
	rm -rf $(CLIENT) $(SERVER)

re:	fclean all
