/*
** names.c for  in /home/karst_j/PSU_2015_myirc
**
** Made by Julien Karst
** Login   <karst_j@epitech.net>
**
** Started on  Wed Jun  1 22:20:54 2016  Julien Karst
** Last update Fri Jun  3 00:43:00 2016 
*/

#include	"irc.h"

static void	print_all_channel(t_channel *chan, int fd)
{
  int		c;
  t_channel     *tmp;

  tmp = chan;
  c = -1;
  while (tmp->root == 0)
    tmp = tmp->next;
  tmp = tmp->next;
  while (tmp->root == 0)
    {
      if (tmp->name[0] == '#' && tmp->fd_type[fd] != FD_FREE)
	{
	  dprintf(fd, ":irc.localhost 353 %s = %s :%s",
		  tmp->nick[fd], tmp->name, tmp->nick[fd]);
	  while (++c < MAX_FD)
	    if (tmp->fd_type[c] != FD_FREE && c != tmp->creator && c != fd)
	      dprintf(fd, " %s", tmp->nick[c]);
	  if (tmp->fd_type[tmp->creator] != FD_FREE)
	    dprintf(fd, " @%s",  tmp->nick[tmp->creator]);
	  dprintf(fd, "\r\n");
	}
      tmp = tmp->next;
    }
}

static void	print_channel(t_channel *chan, int fd, char *str)
{
  int		c;
  t_channel	*tmp;

  c = -1;
  tmp = found_channel_by_name(chan, str);
  dprintf(fd, ":irc.localhost 353 %s = %s :%s",
	  tmp->nick[fd], tmp->name, tmp->nick[fd]);
  while (++c < MAX_FD)
    if (tmp->fd_type[c] != FD_FREE && c != tmp->creator && c != fd)
      dprintf(fd, " %s", tmp->nick[c]);
  if (tmp->fd_type[tmp->creator] != FD_FREE)
    dprintf(fd, " @%s",  tmp->nick[tmp->creator]);
  dprintf(fd, "\r\n");
}

void		cmd_names
(int fd, t_channel *chan,
 fd_set *fd_write, char *arg_one)
{
  (void) fd_write;
  (void) arg_one;
  if (arg_one == NULL)
    print_all_channel(chan, fd);
  else
    print_channel(chan, fd, arg_one);
  dprintf(fd, ":irc.localhost 366 %s * "
	  ":End of /NAMES list.\r\n", chan->nick[fd]);
}
