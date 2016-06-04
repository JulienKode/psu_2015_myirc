/*
** send.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 30 21:07:04 2016
** Last update Sat Jun  4 15:00:06 2016
*/

#include	"irc.h"

void		global_message(t_channel *chan, char *msg)
{
  chan_message(found_channel_by_name(chan, "Accueil"), msg);
}

void		chan_message(t_channel *chan, char *msg)
{
  int		i;
  char		*buf;

  i = 0;
  asprintf(&buf, ":%s\r\n", msg);
  while (i < MAX_FD)
    {
      if (chan->fd_type[i] == FD_CLIENT)
	{
	  circbuff_write(&(data->circbuff[i]), buf);
	  data->circbuff_read[i] = 1;
	}
      i++;
    }
  free(buf);
}

int		send_user(t_channel *chan, char *user, char *msg)
{
  int		i;
  t_channel	*tmp;
  char		*buf;

  asprintf(&buf, ":%s\r\n", msg);
  tmp = found_channel_by_name(chan, "Accueil");
  i = -1;
  while (++i < MAX_FD)
    {
      if (tmp->nick[i] && strcmp(tmp->nick[i], user) == 0)
	{
	  circbuff_write(&(data->circbuff[i]), buf);
	  data->circbuff_read[i] = 1;
	  return (1);
	}
    }
  return (0);
}
