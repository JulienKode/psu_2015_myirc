/*
** main.c for  in /home/karst_j/PSU_2015_myirc/sources
**
** Made by Julien Karst
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 16 10:41:14 2016 Julien Karst
** Last update Mon May 16 10:41:59 2016
*/

#include "irc.h"

t_cmd                   cmds[] =
  {
    {"NICK", &cmd_nick},
    {"LIST", &cmd_list},
    {"JOIN", &cmd_join},
    {"PART", &cmd_part},
    {"USERS", &cmd_users},
    {"MSG", &cmd_msg},
    {"SEND_FILE", &cmd_send},
    {"ACCEPT_FILE", &cmd_accept},
  };

void	cmd_nick(int fd, t_channel *chan, fd_set *fd_write, char *arg_one)
{
  (void) fd;
  (void) chan;
  (void) fd_write;
  (void) arg_one;
}

void	cmd_list(int fd, t_channel *chan, fd_set *fd_write, char *arg_one)
{
  (void) fd;
  (void) chan;
  (void) fd_write;
  (void) arg_one;
}

void	cmd_join(int fd, t_channel *chan, fd_set *fd_write, char *arg_one)
{
  (void) fd;
  (void) chan;
  (void) fd_write;
  (void) arg_one;
}

void	cmd_part(int fd, t_channel *chan, fd_set *fd_write, char *arg_one)
{
  (void) fd;
  (void) chan;
  (void) fd_write;
  (void) arg_one;
}

void	cmd_users(int fd, t_channel *chan, fd_set *fd_write, char *arg_one)
{
  (void) fd;
  (void) chan;
  (void) fd_write;
  (void) arg_one;
}

void	cmd_msg(int fd, t_channel *chan, fd_set *fd_write, char *arg_one)
{
  (void) fd;
  (void) chan;
  (void) fd_write;
  (void) arg_one;
}

void	cmd_send(int fd, t_channel *chan, fd_set *fd_write, char *arg_one)
{
  (void) fd;
  (void) chan;
  (void) fd_write;
  (void) arg_one;
}

void	cmd_accept(int fd, t_channel *chan, fd_set *fd_write, char *arg_one)
{
  (void) fd;
  (void) chan;
  (void) fd_write;
  (void) arg_one;
}

void			send_message(char *buf, t_channel *chan, int fd,
				     fd_set *fd_write)
{
  int			i;

  // Il faudra également s'assurer que i est dans le même channel que fd
  for (i = 0; i < MAX_FD; i++)
    if (i != fd && chan->fd_type[i] == FD_CLIENT && FD_ISSET(i, fd_write))
      dprintf(i, "%s\n", buf);
}

void			parse_cmd(char *buf, t_channel *chan, int fd, fd_set *fd_write)
{
  char			*cmd;
  char			*arg_one;
  int			i;
  int			valid;

  cmd = strtok(buf, " \t");
  arg_one = strtok(NULL, " \t");
  i = 0;
  valid = 0;
  while (i < CMD_NUMBER)
    {
      if (cmd && strcmp(cmds[i].name, cmd) == 0)
	{
	  cmds[i].p(fd, chan, fd_write, arg_one);
	  valid = 1;
	}
      i++;
    }
  if (valid == 0)
    send_message(buf, chan, fd, fd_write);
}

void			client_read(t_channel *chan, int fd, fd_set *fd_read,
				    fd_set *fd_write)
{
  char			*buf;
  int			size;
  size_t		n;
  FILE			*fp;

  n = 4096;
  fp = fdopen(fd, "r");
  buf = NULL;
  (void) fd_read;
  if ((size = getline(&buf, &n, fp)) > 0)
    {
      buf[size - 1] = 0;
      printf("Envoyé depuis le client : %s\n", buf);
      parse_cmd(buf, chan, fd, fd_write);
    }
  else
    {
      printf("Connection closed\n");
      fclose(fp);
      close(fd);
      chan->fd_type[fd] = FD_FREE;
      return;
    }
}

void			add_client(t_channel *chan, int s)
{
  int			cs;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;

  client_sin_len = sizeof(client_sin);
  cs = accept(s, (struct sockaddr *)&client_sin, &client_sin_len);
  chan->fd_type[cs] = FD_CLIENT;
  chan->fct_read[cs] = client_read;
  chan->fct_write[cs] = NULL;
}

void			server_read(t_channel *chan, int fd, fd_set *fd_read,
				    fd_set *fd_write)
{
  (void) fd_read;
  (void) fd_write;
  add_client(chan, fd);
}

void			add_server(t_channel *chan)
{
  int			s;
  struct sockaddr_in	sin;
  int			val;

  val = 1;
  s = socket(PF_INET, SOCK_STREAM, 0);
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(chan->next->port);
  sin.sin_addr.s_addr = INADDR_ANY;
  bind(s, (struct sockaddr*)&sin, sizeof(sin));
  listen(s, 42);
  chan->next->fd_type[s] = FD_SERVER;
  chan->next->fct_read[s] = server_read;
  chan->next->fct_write[s] = NULL;
}

int			main(int ac, char **argv)
{
  t_channel		*chan;
  int			i;
  int			j;
  struct timeval	tv;

  if (ac != 2)
    {
      printf("Usage : ./server [port]\n");
      return (1);
    }
  chan = init_list();
  create_channel(chan, atoi(argv[1]), "Accueil");
  create_channel(chan, atoi(argv[1]), "Global");
  add_server(chan);
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  while (42)
    {
      chan = chan->next;
      while (chan->root == 0)
	{
	  FD_ZERO(&(chan->fd_read));
	  for (i = 0; i < MAX_FD; i++)
	    if (chan->fd_type[i] != FD_FREE)
	      FD_SET(i, &(chan->fd_read));
	  FD_ZERO(&(chan->fd_write));
	  for (i = 0; i < MAX_FD; i++)
	    if (chan->fd_type[i] != FD_FREE)
	      FD_SET(i, &(chan->fd_write));
	  if (select(MAX_FD, &(chan->fd_read), &(chan->fd_write), NULL, &tv) == -1)
	    return (0);
	  for (j = 0; j < MAX_FD; j++)
	    if (FD_ISSET(j, &(chan->fd_read)))
	      chan->fct_read[j](chan, j, &(chan->fd_read), &(chan->fd_write));
      	  chan = chan->next;
	}
    }
  return (0);
}
