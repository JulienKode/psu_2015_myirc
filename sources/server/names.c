/*
** names.c for  in /home/karst_j/PSU_2015_myirc
**
** Made by Julien Karst
** Login   <karst_j@epitech.net>
**
** Started on  Wed Jun  1 22:20:54 2016  Julien Karst
** Last update Wed Jun  1 23:19:08 2016 
*/

#include	"irc.h"

static void	print_all_channel(t_channel *chan, int fd)
{


  dprintf(fd, "366 %s * :End of /NAMES list.\r\n", chan->nick[fd]);
}

static void	print_channel(t_channel *chan, int fd, char *str)
{
  t_channel	*tmp;

  tmp = found_channel_by_name(chan, str);
  dprintf(fd, "366 %s %s :End of /NAMES list.\r\n", chan->nick[fd], str);
  dprintf(fd, "366 %s %s :End of /NAMES list.\r\n", chan->nick[fd], str);
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
}
