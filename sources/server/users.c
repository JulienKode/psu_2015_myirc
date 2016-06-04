/*
** users.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 30 21:40:00 2016
** Last update Thu Jun  2 17:06:47 2016
*/

#include	"irc.h"

int		nb_of_users(t_channel *chan)
{
  int		i;
  int		j;

  i = -1;
  j = 0;
  while (++i < MAX_FD)
    if (chan && chan->fd_type[i] == FD_CLIENT)
      j++;
  return (j);
}

void		cmd_users
(int fd, t_channel *chan,
 fd_set *fd_write, char *arg_one)
{
  char		*buf;
  t_channel	*tmp;
  int		i;

  tmp = chan;
  (void) fd_write;
  (void) arg_one;
  asprintf(&buf, ":irc.localhost 392 :UserID   Terminal  Host\r\n");
  circbuff_write(&(data->circbuff[fd]), buf);
  data->circbuff_read[fd] = 1;

  tmp = found_channel_by_name(chan, "Accueil");
  i = 0;
  while (i < MAX_FD)
    {
      if (tmp->fd_type[i] == FD_CLIENT)
	{
	  asprintf(&buf, ":irc.localhost 393 :%s\r\n", tmp->nick[i]);
	  circbuff_write(&(data->circbuff[fd]), buf);
	  data->circbuff_read[fd] = 1;
	}
      i++;
    }
  asprintf(&buf, ":irc.localhost 394 :End of users\r\n");
  circbuff_write(&(data->circbuff[fd]), buf);
  data->circbuff_read[fd] = 1;
}
