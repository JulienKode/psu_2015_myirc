/*
** main.c for  in /home/karst_j/PSU_2015_myirc/sources
**
** Made by Julien Karst
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 16 10:41:14 2016 Julien Karst
** Last update Sat Jun  4 13:09:01 2016 
*/

#include "irc.h"

t_cmd                   cmds[] =
  {
    {"NICK", &cmd_nick},
    {"LIST", &cmd_list},
    {"JOIN", &cmd_join},
    {"PART", &cmd_part},
    {"USERS", &cmd_users},
    {"PRIVMSG", &cmd_msg},
    {"SEND_FILE", &cmd_send},
    {"ACCEPT_FILE", &cmd_accept},
    {"QUIT", &cmd_quit},
    {"NAMES", &cmd_names}
  };

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

void			parse_cmd(char *buf, t_channel *chan, int fd, fd_set *fd_write)
{
  char			*cmd;
  char			*arg_one;
  int			i;
  int			valid;

  buf[strlen(buf) - 1] = 0;
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
  if (valid == 0 && strlen(buf) > 0)
    dprintf(fd, ":irc.localhost %s %s :Unknown command\r\n", chan->nick[fd], cmd);
}

void			client_read(t_channel *chan, int fd, fd_set *fd_read,
				    fd_set *fd_write)
{
  char			*buf;
  int			size;
  size_t		n;
  FILE			*fp;
  char			*msg;

  n = 4096;
  fp = fdopen(fd, "r");
  buf = NULL;
  (void) fd_read;
  if ((size = getline(&buf, &n, fp)) > 1)
    {
      buf[size - 1] = 0;
      printf("Envoyé depuis le client : %s\r\n", buf); // A retirer
      parse_cmd(buf, chan, fd, fd_write);
    }
  else
    {
      msg = malloc(strlen(chan->nick[fd]) + 28);
      if (msg != NULL)
	{
	  msg = strcpy(msg, chan->nick[fd]);
	  msg = strcat(msg, " QUIT :Disconnected by User");
	  global_message(chan, msg);
	}
      client_exit(chan, fd);
      fclose(fp);
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
  chan->nick[cs] = strdup("Anonymous");
  circbuff_write(&(chan->circbuff[cs]), ":irc.localhost 001 Anonymous "
		 ":Welcome to the Internet Relay"
		 " Network Anonymous!~nobody@127.0.0.1\r\n"
		 ":irc.localhost 002 Anonymous :Your host is irc.localhost, "
		 "running version 1.0\r\n"
		 ":irc.localhost 003 Anonymous :This server was created Sun "
		 "May 29 at 14:00:00\r\n"
		 ":irc.localhost 004 Anonymous :irc.localhost 1.0 aoOirw "
		 "abeiIklmnoOpqrsRstv\r\n");
  chan->circbuff_read[cs] = 1;
  global_message(chan, "An Anonymous USER joined the server !");
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
  chan->next->circbuff_read[s] = 0;
}

int			main(int ac, char **argv)
{
  t_channel		*chan;
  int			i;
  int			j;
  fd_set		fd_read;
  fd_set		fd_write;
  int			fd_ok[MAX_FD];

  if (ac != 2)
    {
      printf("Usage : ./server [port]\n");
      return (1);
    }
  chan = init_list();
  create_channel(chan, atoi(argv[1]), "Accueil", -1);
  add_server(chan);
  while (42)
    {
      chan = chan->next;
      FD_ZERO(&fd_read);
      FD_ZERO(&fd_write);
      FD_SET(3, &fd_read);
      while (chan->root == 0)
	{
	  for (i = 0; i < MAX_FD; i++)
	    if (chan->fd_type[i] == FD_CLIENT)
	      {
		FD_SET(i, &fd_read);
		if (chan->circbuff_read[i])
		  FD_SET(i, &fd_write);
	      }
	  chan = chan->next;
	}
      chan = chan->next;
      if (select(MAX_FD + 1, &fd_read, &fd_write, NULL, NULL) == -1)
	return (0);
      memset(fd_ok, 0, MAX_FD);
      while (chan->root == 0)
	{
	  for (j = 0; j < MAX_FD; j++)
	    {
	      if (fd_ok[j] == 0 && chan->fd_type[j] != FD_FREE)
		{
		  if (FD_ISSET(j, &fd_read))
		    {
		      chan->fct_read[j](chan, j, fd_read, fd_write);
		      fd_ok[j] = 1;
		    }
		  else if (FD_ISSET(j, &fd_write))
		    {
		      client_write(chan, j);
		      fd_ok[j] = 1;
		    }
		}
	    }
	  chan = chan->next;
	}
      while (chan->root == 0)
	chan = chan->next;
    }
  return (0);
}
