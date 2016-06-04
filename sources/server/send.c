/*
** send.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 30 21:07:04 2016
** Last update Sat Jun  4 14:22:03 2016 
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
  buf = NULL;
  while (i < MAX_FD)
    {
      if (chan->fd_type[i] == FD_CLIENT)
	{
	  asprintf(&buf, ":%s\r\n", msg);
	  circbuff_write(&(chan->circbuff[i]), buf);
	  chan->circbuff_read[i] = 1;
	}
      i++;
    }
}

int		send_user(t_channel *chan, char *user, char *msg)
{
  int		i;
  t_channel	*tmp;

  tmp = chan;
  while (tmp->root == 0)
    tmp = tmp->next;
  tmp = tmp->next;
  while (tmp->root == 0)
    {
      i = -1;
      while (++i < MAX_FD)
	{
	  printf("[%s][%s]\n", tmp->nick[i], user);
	  if (tmp->nick[i] && strcmp(tmp->nick[i], user) == 0)
	    {
	      circbuff_write(&(tmp->circbuff[i]), msg);
	      tmp->circbuff_read[i] = 1;
	      return (1);
	    }
	}
      tmp = tmp->next;
    }
  return (0);
}
