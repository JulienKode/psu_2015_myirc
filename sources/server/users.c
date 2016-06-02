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

int		nb_of_users(t_channel *chan, int fd)
{
  t_channel	*tmp;
  int		i;

  i = 0;
  tmp = chan;
  while (tmp->root == 0)
    tmp = tmp->next;
  tmp = tmp->next;
  while (tmp->root == 0)
    {
      if (tmp && tmp->fd_type[fd] != FD_FREE)
	i++;
      tmp = tmp->next;
    }
  return (i);
}

void		cmd_users
(int fd, t_channel *chan,
 fd_set *fd_write, char *arg_one)
{
  int		res;

  (void) fd_write;
  (void) arg_one;
  res = nb_of_users(chan, fd);
  dprintf(fd,
	  ":irc.localhost 265 to :Current local users: %d  Max: %d\r\n"
	  ":irc.localhost 266 to :Current global users: %d  Max: %d\r\n",
	  res, res, res, res );
}
