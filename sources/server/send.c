/*
** send.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 30 21:07:04 2016
** Last update Mon May 30 21:26:44 2016
*/

#include	"irc.h"

void		global_message(t_channel *chan, char *msg)
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
	  if (tmp->fd_type[i] == FD_CLIENT)
	    dprintf(i, ":%s\r\n", msg);
	  i++;
	}
      tmp = tmp->next;
    }
  free(msg);
}

void		chan_message(t_channel *chan, char *msg)
{
  int		i;

  i = 0;
  printf("Debug : chan %s\n", chan->name);
  while (i < MAX_FD)
    {
      if (chan->fd_type[i] == FD_CLIENT /* && FD_ISSET(i, &(chan->fd_write)) */)
	dprintf(i, "%s\r\n", msg);
      i++;
    }
}
