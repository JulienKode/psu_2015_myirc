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
  t_channel	*tmp;
  int		i;
  int		j;

  i = -1;
  j = 0;
  tmp = found_channel_by_name(chan, "Accueil");
  while (++i < MAX_FD)
    if (tmp && tmp->fd_type[i] == FD_CLIENT)
      j++;
  return (j);
}

void		cmd_users
(int fd, t_channel *chan,
 fd_set *fd_write, char *arg_one)
{
  int		res;
  char		*buf;

  (void) fd_write;
  (void) arg_one;
  res = nb_of_users(chan);
  asprintf(&buf,
	  ":irc.localhost 265 to :Current local users: %d  Max: %d\r\n"
	  ":irc.localhost 266 to :Current global users: %d  Max: %d\r\n",
	  res, res, res, res);
  circbuff_write(&(data->circbuff[fd]), buf);
  data->circbuff_read[fd] = 1;
}
