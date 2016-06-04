/*
** names.c for  in /home/karst_j/PSU_2015_myirc
**
** Made by Julien Karst
** Login   <karst_j@epitech.net>
**
** Started on  Wed Jun  1 22:20:54 2016  Julien Karst
** Last update Sat Jun  4 16:56:45 2016 
*/

#include	"irc.h"

static void	add_user(t_channel *tmp, int fd, int c)
{
  char		*buf;

  asprintf(&buf, " %s", tmp->nick[c]);
  send_buff(fd, buf);
}

static void	print_channel_loop(t_channel *tmp, int fd)
{
  char		*buf;
  int		c;

  c = -1;
  asprintf(&buf, ":irc.localhost 353 %s = %s :%s",
	   tmp->nick[fd], tmp->name, tmp->nick[fd]);
  send_buff(fd, buf);
  while (++c < MAX_FD)
    if (tmp->fd_type[c] != FD_FREE && c != tmp->creator && c != fd)
      add_user(tmp, fd, c);
  if (tmp->fd_type[tmp->creator] != FD_FREE)
    {
      asprintf(&buf, " @%s", tmp->nick[tmp->creator]);
      send_buff(fd, buf);
    }
  asprintf(&buf, "\r\n");
  send_buff(fd, buf);
}

static void	print_all_channel(t_channel *chan, int fd)
{
  t_channel     *tmp;

  tmp = chan;
  while (tmp->root == 0)
    tmp = tmp->next;
  tmp = tmp->next;
  while (tmp->root == 0)
    {
      if (tmp->name[0] == '#' && tmp->fd_type[fd] != FD_FREE)
	print_channel_loop(tmp, fd);
      tmp = tmp->next;
    }
}

static void	print_channel(t_channel *chan, int fd, char *str)
{
  int		c;
  t_channel	*tmp;
  char		*buf;

  c = -1;
  tmp = found_channel_by_name(chan, str);
  if (tmp == NULL)
    return;
  asprintf(&buf, ":irc.localhost 353 %s = %s :%s",
	  tmp->nick[fd], tmp->name, tmp->nick[fd]);
  send_buff(fd, buf);
  while (++c < MAX_FD)
    if (tmp->fd_type[c] != FD_FREE && c != tmp->creator && c != fd)
      {
	asprintf(&buf, " %s", tmp->nick[c]);
	send_buff(fd, buf);
      }
  if (tmp->fd_type[tmp->creator] != FD_FREE)
    {
      asprintf(&buf, " @%s",  tmp->nick[tmp->creator]);
      send_buff(fd, buf);
    }
  asprintf(&buf, "\r\n");
  send_buff(fd, buf);
}

void		cmd_names(int fd, t_channel *chan, char *arg_one)
{
  char		*buf;

  (void) arg_one;
  if (arg_one == NULL)
    print_all_channel(chan, fd);
  else
    print_channel(chan, fd, arg_one);
  asprintf(&buf, ":irc.localhost 366 %s * "
	   ":End of /NAMES list.\r\n", chan->nick[fd]);
  send_buff(fd, buf);
}
