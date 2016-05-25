##
## Makefile for Makefile in /home/malot_k/tests/filesystem/my_files
## 
## Made by kevin malot
## Login   <malot_k@epitech.net>
## 
## Started on  Sun Nov 23 10:06:19 2014 kevin malot
## Last update Tue May 12 14:51:52 2015 kevin malot
##

CFLAGS          += -W -Wall -Wextra -Werror -Iincludes -g

LDFLAGS         = 

NAME_SERVER	= server

NAME_CLIENT	= client

SRC_SERVER	= 	sources/server/server.c \
			sources/utils/list.c

SRC_CLIENT	= sources/server/client.c

OBJ_SERVER	= $(SRC_SERVER:.c=.o)

OBJ_CLIENT	= $(SRC_CLIENT:.c=.o)

all:	$(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER):	$(OBJ_SERVER)
	cc $(CFLAGS) -o $(NAME_SERVER) $(OBJ_SERVER) $(LDFLAGS)

$(NAME_CLIENT):	$(OBJ_CLIENT)
	cc $(CFLAGS) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(LDFLAGS)

clean:
	rm -f $(OBJ_SERVER)
	rm -f $(OBJ_CLIENT)

fclean:	clean
	rm -f $(NAME_SERVER)
	rm -f $(NAME_CLIENT)

re: fclean	all
