/*
** join.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 30 18:14:50 2016
** Last update Mon May 30 18:16:26 2016 
*/

#include	"irc.h"

int		join_channel_exist(t_channel *chan, char *channel, int fd)
{
  t_channel	*tmp;
  inti;

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

void		join_set_channel(t_channel *chan, char *channel, int fd)
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

void		cmd_join
(int fd, t_channel *chan,
 fd_set *fd_write, char *chan_name)
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
