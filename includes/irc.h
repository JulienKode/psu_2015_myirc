/*
** irc.h for  in /home/karst_j/PSU_2015_myirc/includes
**
** Made by Julien Karst
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 16 10:40:15 2016 Julien Karst
** Last update Sat Jun  4 19:39:06 2016 
*/

#ifndef			IRC_H_
#define			IRC_H_

#define			FD_FREE		0
#define			FD_CLIENT	1
#define			FD_SERVER	2
#define			MAX_FD		255
#define			CMD_NUMBER	10
#define			_GNU_SOURCE

#include		<sys/select.h>
#include		<sys/time.h>
#include		<sys/types.h>
#include		<sys/socket.h>
#include		<netinet/in.h>
#include		<arpa/inet.h>
#include		<stdio.h>
#include		<string.h>
#include		<stdlib.h>
#include		<unistd.h>
#include		<netdb.h>
#include		"utils_circbuff.h"
#include		<signal.h>

typedef void		(*fct)();

typedef struct		s_channel
{
  int			creator;
  int			root;
  int			port;
  char			*name;
  int			join[MAX_FD];
  char			fd_type[MAX_FD];
  fct			fct_read[MAX_FD];
  char			*nick[MAX_FD];
  struct s_channel	*prev;
  struct s_channel	*next;
}			t_channel;

typedef struct		s_data
{
  int			circbuff_read[MAX_FD];
  t_circbuff		circbuff[MAX_FD];
  t_channel		*chan;
}			t_data;

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

extern t_data		*data;

int			send_user(t_channel*, char*, char*);
int			nick_exists(t_channel *, char *);
int			nb_of_users(t_channel*);
int			join_channel_exist(t_channel *, char *, int);
void			signal_handler(int);
void			send_buff(int, char*);
void			client_write(int);
void			join_set_channel(t_channel *, char *, int, int);
void			global_message(t_channel *, char *);
void			chan_message(t_channel *, char *);
void			cmd_nick(int, t_channel *, char *);
void			cmd_quit(int, t_channel *, char *);
void			cmd_list(int, t_channel *, char *);
void			cmd_join(int, t_channel *, char *);
void			cmd_part(int, t_channel *, char *);
void			cmd_users(int, t_channel *, char *);
void			cmd_msg(int, t_channel *, char *);
void			cmd_send(int, t_channel *, char *);
void			cmd_accept(int, t_channel *, char *);
void			cmd_names(int, t_channel *, char *);
void			create_channel(t_channel *, int, char *, int);
void			client_exit(t_channel *, int);
void			client_nick(t_client*, char*, char*);
void			client_list(t_client*, char*, char*);
void			client_join(t_client*, char*, char*);
void			client_part(t_client*, char*, char*);
void			client_users(t_client*, char*, char*);
void			client_msg(t_client*, char*, char*);
void			client_quit(t_client*, char*, char*);
void			client_help(t_client*, char*, char*);
void			client_send(t_client*, char*, char*);
void			client_accept(t_client*, char*, char*);
t_channel		*found_channel_by_name(t_channel *, char *);
t_channel		*init_list();
void			client_server(t_client *, char*, char *);

#endif			/* IRC_H_ */
