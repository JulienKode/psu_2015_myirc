/*
** nick.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 30 18:16:50 2016
** Last update Fri Jun  3 00:07:02 2016
*/

#include	"irc.h"

void		cmd_nick(int fd, t_channel *chan, char *nick)
{
  char		*msg;

  if (nick == NULL)
    {
      asprintf(&msg, ":irc.localhost 431 * NICK :No nickname given\r\n");
      circbuff_write(&(data->circbuff[fd]), msg);
      data->circbuff_read[fd] = 1;
    }
  else if (nick_exists(chan, nick))
    {
      asprintf(&msg, ":irc.localhost 433 * %s "
	       ":Nickname is already in use\r\n", nick);
      circbuff_write(&(data->circbuff[fd]), msg);
      data->circbuff_read[fd] = 1;
    }
  else
    {
      asprintf(&msg, "%s NICK %s", chan->nick[fd], nick);
      global_message(chan, msg);
      chan->nick[fd] = strdup(nick);
    }
}

int		nick_exists(t_channel *chan, char *nick)
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
	  if (tmp->nick && tmp->nick[i] && strcmp(tmp->nick[i], nick) == 0)
	    return (1);
	  i++;
	}
      tmp = tmp->next;
    }
  return (0);
}
