/*
** main.c for  in /home/karst_j/PSU_2015_myirc/sources
**
** Made by Julien Karst
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 16 10:41:14 2016 Julien Karst
** Last update Mon May 16 10:41:59 2016
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "irc.h"

#define FD_FREE 0
#define FD_CLIENT 1
#define FD_SERVER 2
#define MAX_FD 255

typedef void(*fct)();

typedef struct	s_env
{
  char		fd_type[MAX_FD];
  fct		fct_read[MAX_FD];
  fct		fct_write[MAX_FD];
  int		port;
}		t_env;

void		client_read(t_env *e, int fd)
{
  int		r;
  char		buf[4096];
  int		i;

  r = read(fd, buf, 4096);
  if (r > 0)
    {
      buf[r] = '\0';
      for (i = 0; i < MAX_FD; i++)
	if (i != fd && e->fd_type[i] == FD_CLIENT)
	  write(i, buf, r);
    }
  else
    {
      printf("Connection closed\n");
      close(fd);
      e->fd_type[fd] = FD_FREE;
    }
}

void			add_client(t_env *e, int s)
{
  int			cs;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;

  client_sin_len = sizeof(client_sin);
  cs = accept(s, (struct sockaddr *)&client_sin, &client_sin_len);
  e->fd_type[cs] = FD_CLIENT;
  e->fct_read[cs] = client_read;
  e->fct_write[cs] = NULL;
}

void			server_read(t_env *e, int fd)
{
  add_client(e, fd);
}

void			add_server(t_env *e)
{
  int			s;
  struct sockaddr_in	sin;
  int			val;

  val = 1;
  s = socket(PF_INET, SOCK_STREAM, 0);
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(e->port);
  sin.sin_addr.s_addr = INADDR_ANY;
  bind(s, (struct sockaddr*)&sin, sizeof(sin));
  listen(s, 42);
  e->fd_type[s] = FD_SERVER;
  e->fct_read[s] = server_read;
  e->fct_write[s] = NULL;
}

int			main(int ac, char **argv)
{
  t_env			e;
  int			i;
  int			j;
  fd_set		fd_read;
  struct timeval	tv;

  if (ac == 2)
    {
      memset(e.fd_type, FD_FREE, MAX_FD);
      e.port = atoi(argv[1]);
      add_server(&e);
      tv.tv_sec = 0;
      tv.tv_usec = 0;
      while (42)
	{
	  FD_ZERO(&fd_read);
	  for (i = 0; i < MAX_FD; i++)
	    if (e.fd_type[i] != FD_FREE)
	      FD_SET(i, &fd_read);
	  if (select(MAX_FD, &fd_read, NULL, NULL, &tv) == -1)
	    {
	      perror("select");
	      exit(42);
	    }
	  for (j = 0; j < MAX_FD; j++)
	    if (FD_ISSET(j, &fd_read))
	      e.fct_read[j](&e, j);
	}
    }
  return (0);
}
