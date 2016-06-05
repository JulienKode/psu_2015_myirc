/*
** parser.c for parser in /home/malot_k/PSU/psu_2015_myirc/sources/server
**
** Made by Kevin Malot
** Login   <malot_k@epitech.net>
**
** Started on  Sun Jun  5 22:20:15 2016 Kevin Malot
** Last update Sun Jun  5 22:20:15 2016 Kevin Malot
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

void			parse_cmd(char *buf, t_channel *chan, int fd)
{
  char			*cmd;
  char			*arg_one;
  char			*tmp;
  int			valid;
  int			i;

  cmd = strtok(buf, " \t");
  arg_one = strtok(NULL, " \t");
  i = 0;
  valid = 0;
  while (i < CMD_NUMBER)
    {
      if (cmd && strcmp(cmds[i].name, cmd) == 0)
	{
	  cmds[i].p(fd, chan, arg_one);
	  valid = 1;
	}
      i++;
    }
  if (valid == 0 && strlen(buf) > 0)
    {
      asprintf(&tmp, ":irc.localhost %s %s :Unknown command\r\n",
	       chan->nick[fd], cmd);
      send_buff(fd, tmp);
    }
}

void			client_read(t_channel *chan, int fd)
{
  char			*buf;
  int			size;
  size_t		n;
  FILE			*fp;
  char			*msg;

  n = 4096;
  fp = fdopen(fd, "r");
  buf = NULL;
  if ((size = getline(&buf, &n, fp)) > 1)
    {
      buf[size - 2] = 0;
      parse_cmd(buf, chan, fd);
    }
  else
    {
      asprintf(&msg, "%s QUIT :Disconnected by User", chan->nick[fd]);
      global_message(chan, msg);
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
  circbuff_write(&(data->circbuff[cs]), ":irc.localhost 001 Anonymous "
		 ":Welcome to the Internet Relay"
		 " Network Anonymous!~nobody@127.0.0.1\r\n"
		 ":irc.localhost 002 Anonymous :Your host is "
		 "irc.localhost, running version 1.0\r\n"
		 ":irc.localhost 003 Anonymous :This server was created Sun "
		 "May 29 at 14:00:00\r\n"
		 ":irc.localhost 004 Anonymous :irc.localhost 1.0 aoOirw "
		 "abeiIklmnoOpqrsRstv\r\n");
  data->circbuff_read[cs] = 1;
  global_message(chan, "An Anonymous USER joined the server !");
}
