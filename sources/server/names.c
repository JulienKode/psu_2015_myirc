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
  char		*buf;

  tmp = chan;
  c = -1;
  while (tmp->root == 0)
    tmp = tmp->next;
  tmp = tmp->next;
  while (tmp->root == 0)
    {
      if (tmp->name[0] == '#' && tmp->fd_type[fd] != FD_FREE)
	{
	  asprintf(&buf, ":irc.localhost 353 %s = %s :%s",
		  tmp->nick[fd], tmp->name, tmp->nick[fd]);
	  circbuff_write(&(data->circbuff[fd]), buf);
	  data->circbuff_read[fd] = 1;
	  while (++c < MAX_FD)
	    if (tmp->fd_type[c] != FD_FREE && c != tmp->creator && c != fd)
	      {
		asprintf(&buf, " %s", tmp->nick[c]);
		circbuff_write(&(data->circbuff[fd]), buf);
		data->circbuff_read[fd] = 1;
	      }
	  if (tmp->fd_type[tmp->creator] != FD_FREE)
	    {
	      asprintf(&buf, " @%s",  tmp->nick[tmp->creator]);
	      circbuff_write(&(data->circbuff[fd]), buf);
	      data->circbuff_read[fd] = 1;
	    }
	  asprintf(&buf, "\r\n");
	  circbuff_write(&(data->circbuff[fd]), buf);
	  data->circbuff_read[fd] = 1;
	}
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
  circbuff_write(&(data->circbuff[fd]), buf);
  data->circbuff_read[fd] = 1;
  while (++c < MAX_FD)
    if (tmp->fd_type[c] != FD_FREE && c != tmp->creator && c != fd)
      {
	asprintf(&buf, " %s", tmp->nick[c]);
	circbuff_write(&(data->circbuff[fd]), buf);
	data->circbuff_read[fd] = 1;
      }
  if (tmp->fd_type[tmp->creator] != FD_FREE)
    {
      asprintf(&buf, " @%s",  tmp->nick[tmp->creator]);
      circbuff_write(&(data->circbuff[fd]), buf);
      data->circbuff_read[fd] = 1;
    }
  asprintf(&buf, "\r\n");
  circbuff_write(&(data->circbuff[fd]), buf);
  data->circbuff_read[fd] = 1;
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
  circbuff_write(&(data->circbuff[fd]), buf);
  data->circbuff_read[fd] = 1;
}
