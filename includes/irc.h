/*
** irc.h for  in /home/karst_j/PSU_2015_myirc/includes
**
** Made by Julien Karst
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 16 10:40:15 2016 Julien Karst
** Last update Mon May 16 10:41:05 2016
*/

#ifndef	IRC_H_
#define	IRC_H_

#define	FD_FREE 0
#define	FD_CLIENT 1
#define FD_SERVER 2
#define MAX_FD 255
#define CMD_NUMBER 8

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef void		(*fct)();

typedef struct		s_channel
{
  int			root;
  int			port;
  char			*name;
  struct s_channel	*prev;
  struct s_channel	*next;
  fd_set		fd_read;
  fd_set		fd_write;
  char			fd_type[MAX_FD];
  fct			fct_read[MAX_FD];
  fct			fct_write[MAX_FD];
}			t_channel;

typedef struct		s_cmd
{
  char			*name;
  void			(*p)(int, t_channel *, fd_set *, char *);
}			t_cmd;

void			cmd_nick(int, t_channel *, fd_set *, char *);
void			cmd_list(int, t_channel *, fd_set *, char *);
void			cmd_join(int, t_channel *, fd_set *, char *);
void			cmd_part(int, t_channel *, fd_set *, char *);
void			cmd_users(int, t_channel *, fd_set *, char *);
void			cmd_msg(int, t_channel *, fd_set *, char *);
void			cmd_send(int, t_channel *, fd_set *, char *);
void			cmd_accept(int, t_channel *, fd_set *, char *);
void			create_channel(t_channel *, int, char *);
t_channel		*init_list();

#endif	/* IRC_H_ */
