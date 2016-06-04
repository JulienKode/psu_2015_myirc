/*
** join.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 30 18:14:50 2016
** Last update Sat Jun  4 14:55:41 2016 
*/

#include	"irc.h"

int		join_channel_exist(t_channel *chan, char *channel, int fd)
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

static void	join_c(int fd, t_channel *chan, char *chan_name, int c)
{
  char		*buf;

  if (chan->join[fd] == 0 && c != 0)
    {
      chan->join[fd] = 1;
      if (c == 1)
	{
	  asprintf(&buf, ":irc.localhost MODE %s +nt\r\n"
		  ":irc.localhost 353 %s = %s :@%s",
		  chan_name, chan->nick[fd], chan_name, chan->nick[fd]);
	  circbuff_write(&(data->circbuff[fd]), buf);
	  data->circbuff_read[fd] = 1;
	}
      else
	{
	  asprintf(&buf, ":irc.localhost 353 %s = %s :%s",
		  chan->nick[fd], chan_name, chan->nick[fd]);
	  circbuff_write(&(data->circbuff[fd]), buf);
	  data->circbuff_read[fd] = 1;
	  while (++c < MAX_FD)
	    if (chan->fd_type[c] != FD_FREE && c != chan->creator
		&& c != fd)
	      {
		asprintf(&buf, " %s", chan->nick[c]);
		circbuff_write(&(data->circbuff[fd]), buf);
		data->circbuff_read[fd] = 1;
	      }
	  if (chan->fd_type[chan->creator] != FD_FREE)
	    {
	      asprintf(&buf, " @%s", chan->nick[chan->creator]);
	      circbuff_write(&(data->circbuff[fd]), buf);
	      data->circbuff_read[fd] = 1;
	    }
	}
      asprintf(&buf, "\r\n:irc.localhost 366 %s %s :End of /NAMES list.\r\n",
	      chan->nick[fd], chan_name);
      circbuff_write(&(data->circbuff[fd]), buf);
      data->circbuff_read[fd] = 1;
    }
}

void		join_set_channel
(t_channel *chan, char *channel, int fd, int c)
{
  char		*msg;
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
	  asprintf(&msg, "%s!~%s@localhost JOIN :%s",
		   tmp->nick[fd], tmp->nick[fd], channel);
	  chan_message(tmp, msg);
	  join_c(fd, tmp, channel, c);
	  return;
	}
      tmp = tmp->next;
    }
}


void		cmd_join
(int fd, t_channel *chan,
 fd_set *fd_write, char *chan_name)
{
  char		*buf;

  (void) fd_write;
  if (chan_name == NULL)
    {
      asprintf(&buf, ":irc.localhost 461 * NICK :Not enough parameters\r\n");
      circbuff_write(&(data->circbuff[fd]), buf);
      data->circbuff_read[fd] = 1;
    }
  else if (chan_name[0] != '#')
    {
      asprintf(&buf, ":irc.localhost 433 * %s"
	       " :Illegal channel name\r\n", chan_name);
      circbuff_write(&(data->circbuff[fd]), buf);
      data->circbuff_read[fd] = 1;
    }
  else
    {
      if (join_channel_exist(chan, chan_name, fd) == 1)
	join_set_channel(chan, chan_name, fd, -1);
      else
	{
	  create_channel(chan, chan->port, chan_name, fd);
	  join_set_channel(chan, chan_name, fd, 1);
	}
    }
}
