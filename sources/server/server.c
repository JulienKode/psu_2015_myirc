/*
** main.c for  in /home/karst_j/PSU_2015_myirc/sources
**
** Made by Julien Karst
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 16 10:41:14 2016 Julien Karst
** Last update Mon May 30 21:09:08 2016 
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
    {"QUIT", &cmd_quit},
  };

int		nick_exists(t_channel *chan, char *nick)
{
  t_channel	*tmp;
  int		i;

  tmp = chan;
  while (tmp->root == 0)
     tmp = tmp->next;
  tmp = tmp->next;
  while (tmp->root == 0)
    {
      i = 0;
      while (i < MAX_FD)
	{
	  if (tmp->nick && tmp->nick[i] && strcmp(tmp->nick[i], nick) == 0)
	    return (1);
	  i++;
	}
      tmp = tmp->next;
    }
  return (0);
}

void	cmd_quit(int fd, t_channel *chan, fd_set *fd_write, char *reason)
{
  char	*msg;

  (void) fd_write;
  if (reason != NULL)
    msg = malloc(strlen(chan->nick[fd]) + 8 + strlen(reason));
  else
    msg = malloc(strlen(chan->nick[fd]) + 8);
  if (msg == NULL)
    exit(42);
  msg = strcpy(msg, chan->nick[fd]);
  msg = strcat(msg, " QUIT ");
  close(fd);
  chan->fd_type[fd] = FD_FREE;
  if (reason != NULL)
    msg = strcat(msg, reason);
  global_message(chan, msg);
}

void	cmd_nick(int fd, t_channel *chan, fd_set *fd_write, char *nick)
{
  char	*msg;

  (void) fd_write;
  if (nick == NULL)
    dprintf(fd, "431 * NICK :No nickname given\r\n");
  else if (nick_exists(chan, nick))
    dprintf(fd, "433 * %s :Nickname is already in use\r\n", nick);
  else
    {
      msg = malloc(7 + strlen(chan->nick[fd]) + strlen(nick));
      if (msg == NULL)
	exit(42);
      msg = strcpy(msg, chan->nick[fd]);
      msg = strcat(msg, " NICK ");
      msg = strcat(msg, nick);
      global_message(chan, msg);
      nick[strlen(nick) - 1] = 0;
      chan->nick[fd] = strdup(nick);
    }
}

void	cmd_list(int fd, t_channel *chan, fd_set *fd_write, char *arg_one)
{
  t_channel	*tmp;

  tmp = chan;
  (void) fd_write;
  (void) arg_one;
  while (tmp->root == 0)
     tmp = tmp->next;
  tmp = tmp->next;
  dprintf(fd, "321 %s Channel :Users  Name\r\n", chan->nick[fd]);
  while (tmp->root == 0)
    {
      if (arg_one && tmp->name && strstr(tmp->name, arg_one) != NULL)
	dprintf(fd, "322 %s %s 1 :\r\n", chan->nick[fd], tmp->name);
      else if (tmp->name && arg_one == NULL)
	dprintf(fd, "322 %s %s 1 :\r\n", chan->nick[fd], tmp->name);
      tmp = tmp->next;
    }
  dprintf(fd, "323 %s :End of /LIST\r\n", chan->nick[fd]);
}

int	        join_channel_exist(t_channel *chan, char *channel, int fd)
{
  t_channel	*tmp;
  int		i;

  i = 0;
  (void) fd;
  tmp = chan;
  while (tmp->root == 0)
     tmp = tmp->next;
  tmp = tmp->next;
  while (tmp->root == 0)
    {
      if (tmp->name && strcmp(tmp->name, channel) == 0)
	  i = 1;
      tmp = tmp->next;
    }
  return (i);
}

void	        join_set_channel(t_channel *chan, char *channel, int fd)
{
  t_channel	*tmp;

  tmp = chan;
  while (tmp->root == 0)
     tmp = tmp->next;
  tmp = tmp->next;
  while (tmp->root == 0)
    {
      if (strcmp(tmp->name, channel) == 0)
	{
	  tmp->nick[fd] = chan->nick[fd];
	  tmp->fd_type[fd] = chan->fd_type[fd];
	  tmp->fct_read[fd] = chan->fct_read[fd];
	  chan->fd_type[fd] = FD_FREE;
	}
      tmp = tmp->next;
    }
}

void	cmd_join(int fd, t_channel *chan, fd_set *fd_write, char *chan_name)
{
  (void) fd_write;
  if (chan_name == NULL)
    dprintf(fd, "461 * NICK :Not enough parameters\r\n");
  else if (chan_name[0] != '#')
    dprintf(fd, "433 * %s :Illegal channel name\r\n", chan_name);
  else
    {
      chan_name[strlen(chan_name) - 1] = 0;
      if (join_channel_exist(chan, chan_name, fd) == 1)
	join_set_channel(chan, chan_name, fd);
      else
	{
	  create_channel(chan, chan->port, chan_name);
	  join_set_channel(chan, chan_name, fd);
	  dprintf(fd, ":%s!~%s@localhost JOIN :%s\r\n"
		  "MODE %s +nt\r\n"
		  "353 %s = %s :@%s\r\n"
		  "366 %s %s :End of /NAMES list.\r\n", chan->nick[fd]
		  , chan->nick[fd], chan_name, chan_name, chan->nick[fd],
		  chan_name, chan->nick[fd], chan->nick[fd], chan_name);
	}
    }
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
  chan_message(chan, "Tu est sur le channel\r\n");
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

  for (i = 0; i < MAX_FD; i++)
    if (i != fd && chan->fd_type[i] == FD_CLIENT && FD_ISSET(i, fd_write))
      dprintf(i, "%s\r\n", buf);
}

void			parse_cmd(char *buf, t_channel *chan, int fd, fd_set *fd_write)
{
  char			*cmd;
  char			*arg_one;
  int			i;
  int			valid;
  char			*buf_tmp;

  buf_tmp = strdup(buf);
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
    send_message(buf_tmp, chan, fd, fd_write);
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
      printf("Envoyé depuis le client : %s\r\n", buf); // A retirer
      parse_cmd(buf, chan, fd, fd_write);
    }
  else
    {
      printf("Connection closed\r\n"); // A modifier
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
  chan->nick[cs] = strdup("Anonymous");
  dprintf(cs, ":irc.localhost 001 Anonymous :Welcome to the Internet Relay"
	  " Network Anonymous!~nobody@127.0.0.1\r\n"
	  ":irc.localhost 002 Anonymous :Your host is irc.localhost, "
	  "running version 1.0\r\n"
	  ":irc.localhost 003 Anonymous :This server was created Sun May "
	  "29 at 14:00:00\r\n"
	  ":irc.localhost 004 Anonymous :irc.localhost 1.0 aoOirw "
	  "abeiIklmnoOpqrsRstv\r\n");
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
