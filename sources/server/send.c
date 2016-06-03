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

  tmp = chan;
  while (tmp->root == 0)
    tmp = tmp->next;
  tmp = tmp->next;
  while (tmp->root == 0)
    {
      chan_message(tmp, msg);
      tmp = tmp->next;
    }
}

void		chan_message(t_channel *chan, char *msg)
{
  int		i;
  char		*buf;

  i = 0;
  while (i < MAX_FD)
    {
      if (chan->fd_type[i] == FD_CLIENT)
	{
	  buf = malloc(strlen(msg) + 6);
	  if (buf == NULL)
	    return;
	  sprintf(buf, ":%s\r\n", msg);
	  circbuff_write(&(chan->circbuff[i]), buf);
	  chan->circbuff_read[i] = 1;
	}
      i++;
    }
}
