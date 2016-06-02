/*
** irc.h for  in /home/karst_j/PSU_2015_myirc/includes
**
** Made by Julien Karst
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 16 10:40:15 2016 Julien Karst
** Last update Wed Jun  1 22:32:48 2016
*/

#ifndef	IRC_H_
#define	IRC_H_

#define	FD_FREE 0
#define	FD_CLIENT 1
#define FD_SERVER 2
#define MAX_FD 255
#define CMD_NUMBER 9
#define CMD_CLIENT_NUMBER 11

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
#include <netdb.h>

typedef void		(*fct)();

typedef struct		s_channel
{
  int			creator;
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
  char			*nick[MAX_FD];
}			t_channel;

typedef struct		s_cmd
{
  char			*name;
  void			(*p)();
}			t_cmd;

typedef struct		s_client
{
  int			fd;
  fd_set		fd_read;
  fd_set		fd_write;
  struct sockaddr_in	sin;
  socklen_t		len;
}			t_client;

int			nick_exists(t_channel *, char *);
void			join_set_channel(t_channel *, char *, int);
int			join_channel_exist(t_channel *, char *, int);
void			global_message(t_channel *, char *);
void			chan_message(t_channel *, char *);
void			cmd_nick(int, t_channel *, fd_set *, char *);
void			cmd_quit(int, t_channel *, fd_set *, char *);
void			cmd_list(int, t_channel *, fd_set *, char *);
void			cmd_join(int, t_channel *, fd_set *, char *);
void			cmd_part(int, t_channel *, fd_set *, char *);
void			cmd_users(int, t_channel *, fd_set *, char *);
void			cmd_msg(int, t_channel *, fd_set *, char *);
void			cmd_send(int, t_channel *, fd_set *, char *);
void			cmd_accept(int, t_channel *, fd_set *, char *);
void			create_channel(t_channel *, int, char *, int);
t_channel		*found_channel_by_name(t_channel *, char *);
t_channel		*init_list();
void			client_server(t_client *, char*, char *);

#endif	/* IRC_H_ */
