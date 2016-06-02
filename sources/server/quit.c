/*
** quit.c for quit in /home/malot_k/PSU/psu_2015_myirc/sources/server
**
** Made by Kevin Malot
** Login   <malot_k@epitech.net>
**
** Started on  Mon May 30 22:04:15 2016 Kevin Malot
** Last update Thu Jun  2 17:06:10 2016 
*/

#include "irc.h"

void		cmd_quit(int fd, t_channel *chan, fd_set *fd_write,
			 char *reason)
{
  char		*msg;

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
      if (strcmp("*", channel) == 0 || strcmp(tmp->name, channel) == 0)
	{
	  valid = 1;
	  if (tmp->fd_type[fd] == FD_FREE)
	    dprintf(fd, ":irc.localhost 442 * channel :You're not on that channel !\r\n");
	  else
	    {
	      tmp->fd_type[fd] = FD_FREE;
	      msg = malloc(7 + strlen(chan->nick[fd]) + strlen(channel));
	      if (msg == NULL)
		exit(42);
	      msg = strcpy(msg, chan->nick[fd]);
	      msg = strcat(msg, " PART ");
	      msg = strcat(msg, channel);
	      chan_message(chan, msg);
	    }
	}
      tmp = tmp->next;
    }
  if (valid == 0)
    dprintf(fd, ":irc.localhost 403 * %s: No such channel\r\n", channel);
}

void		cmd_part(int fd, t_channel *chan, fd_set *fd_write,
			 char *arg_one)
{
  (void) fd_write;
  printf("Arg : %s\n", arg_one);
  if (arg_one == NULL)
    dprintf(fd, ":irc.localhost 461 * NICK :Not enough parameters\r\n");
  else if (strcmp(arg_one, "Accueil") == 0)
    dprintf(fd, ":irc.localhost 403 * Accueil: No such channel\r\n");
  else
    {
      join_remove_channel(chan, arg_one, fd);
      join_set_channel(chan, "Accueil", fd);
    }
}
