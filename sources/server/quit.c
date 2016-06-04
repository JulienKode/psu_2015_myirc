/*
** quit.c for quit in /home/malot_k/PSU/psu_2015_myirc/sources/server
**
** Made by Kevin Malot
** Login   <malot_k@epitech.net>
**
** Started on  Mon May 30 22:04:15 2016 Kevin Malot
** Last update Fri Jun  3 10:27:09 2016
*/

#include "irc.h"

void		client_exit(t_channel *chan, int fd)
{
  t_channel	*tmp;

  memset(data->circbuff[fd].buffer, 0, 1024);
  data->circbuff_read[fd] = 0;
  tmp = chan;
  while (tmp->root == 0)
    tmp = tmp->next;
  tmp = tmp->next;
  while (tmp->root == 0)
    {
      tmp->fd_type[fd] = FD_FREE;
      tmp = tmp->next;
    }
  close(fd);
}

void		cmd_quit(int fd, t_channel *chan, char *reason)
{
  char		*msg;

  if (reason == NULL)
    asprintf(&msg, "%s QUIT", chan->nick[fd]);
  else
    asprintf(&msg, "%s QUIT :%s", chan->nick[fd], reason);
  global_message(chan, msg);
  client_exit(chan, fd);
}

int		join_remove_check(t_channel *tmp, char *channel, int fd, int valid)
{
  char		*msg;

  if (strcmp("*", channel) == 0 || strcmp(tmp->name, channel) == 0)
    {
      valid = 1;
      if (tmp->fd_type[fd] == FD_FREE)
	{
	  asprintf(&msg, ":irc.localhost 442 * channel "
		   ":You're not on that channel !\r\n");
	  circbuff_write(&(data->circbuff[fd]), msg);
	  data->circbuff_read[fd] = 1;
	}
      else
	{
	  asprintf(&msg, "%s PART %s", tmp->nick[fd], channel);
	  chan_message(tmp, msg);
	  tmp->fd_type[fd] = FD_FREE;
	}
    }
  return (valid);
}

void		join_remove_channel(t_channel *chan, char *channel, int fd)
{
  t_channel	*tmp;
  char		*msg;
  int		valid;

  valid = 0;
  tmp = chan;
  while (tmp->root == 0)
    tmp = tmp->next;
  tmp = tmp->next;
  while (tmp->root == 0)
    {
      valid = join_remove_check(tmp, channel, fd, valid);
      tmp = tmp->next;
    }
  if (valid == 0)
    {
      asprintf(&msg, ":irc.localhost 403 * %s: No such channel\r\n", channel);
      circbuff_write(&(data->circbuff[fd]), msg);
      data->circbuff_read[fd] = 1;
    }
}

void		cmd_part(int fd, t_channel *chan, char *arg_one)
{
  char		*buf;

  if (arg_one == NULL)
    {
      asprintf(&buf, ":irc.localhost 461 * NICK :Not enough parameters\r\n");
      circbuff_write(&(data->circbuff[fd]), buf);
      data->circbuff_read[fd] = 1;
    }
  else if (strcmp(arg_one, "Accueil") == 0)
    {
      asprintf(&buf, ":irc.localhost 403 * Accueil:"
	       " Can't leave the main channel\r\n");
      circbuff_write(&(data->circbuff[fd]), buf);
      data->circbuff_read[fd] = 1;
    }
  else
    join_remove_channel(chan, arg_one, fd);
}
