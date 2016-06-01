/*
** list.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 30 22:35:33 2016
** Last update Mon May 30 22:37:27 2016 
*/

#include	"irc.h"

void		cmd_list
(int fd, t_channel *chan,
 fd_set *fd_write, char *arg_one)
{
  t_channel	*tmp;

  tmp = chan;
  (void) fd_write;
  while (tmp->root == 0)
    tmp = tmp->next;
  tmp = tmp->next;
  dprintf(fd, "321 %s Channel :Users  Name\r\n", chan->nick[fd]);
  while (tmp->root == 0)
    {
      if (arg_one && tmp->name && strstr(tmp->name, arg_one) != NULL)
	dprintf(fd, "322 %s %s 1 :\r\n", chan->nick[fd], tmp->name);
      else if (tmp->name && arg_one == NULL)
	dprintf(fd, "322 %s %s 1 :\r\n", chan->nick[fd], tmp->name);
      tmp = tmp->next;
    }
  dprintf(fd, "323 %s :End of /LIST\r\n", chan->nick[fd]);
}
