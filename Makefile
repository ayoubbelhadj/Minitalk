# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelhadj <abelhadj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/24 22:23:23 by abelhadj          #+#    #+#              #
#    Updated: 2022/12/29 13:33:49 by abelhadj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = MINITALK

FILES = server.c

FILEC = client.c

BFILES = server_bonus.c

BFILEC = client_bonus.c

INCLUDE = minitalk.h

CC = cc 

CFLAGS = -Wall -Wextra -Werror

OBJS = ${FILES:.c=.o}

OBJC = ${FILEC:.c=.o}

B_OBJS = ${BFILES:.c=.o}

B_OBJC = ${BFILEC:.c=.o}

all:$(NAME)

$(NAME): $(OBJS) $(OBJC)
	@$(CC) $(CFLAGS) $(OBJS) -I $(INCLUDE) -o server
	@$(CC) $(CFLAGS) $(OBJC) -I $(INCLUDE) -o client
	@echo "✔️ ALL GOOD"

%.o : %.c $(INCLUDE)
	@gcc  $(CFLAGS) -o $@ -c $<

bonus: $(B_OBJS) $(B_OBJC)
	@$(CC) $(CFLAGS) $(B_OBJS) -I $(INCLUDE) -o bserver
	@$(CC) $(CFLAGS) $(B_OBJC) -I $(INCLUDE) -o bclient
	@echo "✔️ ALL GOOD: BONUS"
clean:
	@rm -f ${OBJS} $(B_OBJS) $(B_OBJC) ${OBJC}
	@echo "✔️ DELETE OBJECTS"

fclean: clean
	@rm -f server bserver client bclient
	@echo "✔️ DELETE ALL"

re: fclean all
