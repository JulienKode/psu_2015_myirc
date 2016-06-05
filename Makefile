##
## Makefile for Makefile in /home/malot_k/tests/filesystem/my_files
## 
## Made by kevin malot
## Login   <malot_k@epitech.net>
## 
## Started on  Sun Nov 23 10:06:19 2014 kevin malot
## Last update Sun Jun  5 22:01:42 2016 
##

CFLAGS          += -W -Wall -Wextra -Werror -Iincludes/server -g

LDFLAGS         = 

NAME_SERVER	= server

SRC_SERVER	= 	sources/server/server.c 		\
			sources/utils/list.c 			\
			sources/server/send.c			\
			sources/server/data.c			\
			sources/server/send_file.c		\
			sources/server/accept_file.c		\
			sources/server/signal_handler.c		\
			sources/server/nick.c			\
			sources/server/msg.c			\
			sources/server/join.c			\
			sources/server/quit.c			\
			sources/server/names.c			\
			sources/server/send_buff.c		\
			sources/server/writer.c			\
			sources/server/users.c			\
			sources/utils/circbuff/circbuff.c	\
			sources/server/list.c

OBJ_SERVER	= $(SRC_SERVER:.c=.o)

all:	$(NAME_SERVER) client

$(NAME_SERVER):	$(OBJ_SERVER)
	cc $(CFLAGS) -o $(NAME_SERVER) $(OBJ_SERVER) $(LDFLAGS)

client:
	make -C sources/client/build-Interface-Desktop-Debug
	cp sources/client/build-Interface-Desktop-Debug/client .
clean:
	rm -f $(OBJ_SERVER)
	rm -f sources/client/build-Interface-Desktop-Debug/*.o

fclean:	clean
	rm -f $(NAME_SERVER)
	rm -f client

re: fclean	all
