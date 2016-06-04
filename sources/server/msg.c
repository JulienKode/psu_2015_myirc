/*
** msg.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 30 22:48:45 2016
** Last update Sat Jun  4 14:26:12 2016 
*/

#include	"irc.h"

static void	msg_error
(t_channel *chan, int fd, char *arg_one)
{
  char		*msg;

  msg = NULL;
  asprintf(&msg, ":irc.localhost 401 %s %s :No such nick/channel\r\n"
	   , chan->nick[fd], arg_one);
  circbuff_write(&(chan->circbuff[fd]), msg);
}

static int	msg_gere_error
(t_channel *chan, char *arg_one, char *data, int fd)
{
  char		*msg;

  msg = NULL;
  if (arg_one == NULL)
    {
      asprintf(&msg, ":irc.localhost 411 %s :No recipient given (PRIVMSG)"
	       , chan->nick[fd]);
      circbuff_write(&(chan->circbuff[fd]), msg);
      return (0);
    }
  if (data == NULL)
    {
      asprintf(&msg, ":irc.localhost 412 %s :No text to send\r\n"
	       , chan->nick[fd]);
      circbuff_write(&(chan->circbuff[fd]), msg);
      return (0);
    }
  return (1);
}

void		cmd_msg
(int fd, t_channel *chan,
 fd_set *fd_write, char *arg_one)
{
  t_channel	*tmp;
  char		*data;
  char		*msg;

  (void) fd_write;
  data = strtok(NULL, " \t");
  if (msg_gere_error(chan, arg_one, data, fd) == 0)
    return;
  asprintf(&msg, ":%s!~%s@localhost PRIVMSG %s :%s\r\n",
	   chan->nick[fd], chan->nick[fd], arg_one, data);
  if (arg_one && arg_one[0] == '#')
    {
      tmp = found_channel_by_name(chan, arg_one);
      if (tmp != NULL)
	chan_message(tmp, msg);
      else
	msg_error(chan, fd, arg_one);
    }
  else if (arg_one)
    {
      if (send_user(chan, arg_one, msg) == 1)
	return;
      msg_error(chan, fd, arg_one);
    }
}
