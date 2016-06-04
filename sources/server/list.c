/*
1;2802;0c** list.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 30 22:35:33 2016
** Last update Thu Jun  2 17:05:01 2016
*/

#include	"irc.h"

void		cmd_list
(int fd, t_channel *chan,
 fd_set *fd_write, char *arg_one)
{
  t_channel	*tmp;
  char		*buf;

  tmp = chan;
  (void) fd_write;
  while (tmp->root == 0)
    tmp = tmp->next;
  tmp = tmp->next;
  asprintf(&buf, ":irc.localhost 321 %s Channel :Users  Name\r\n",
	   chan->nick[fd]);
  circbuff_write(&(data->circbuff[fd]), buf);
  data->circbuff_read[fd] = 1;
  while (tmp->root == 0)
    {
      if (arg_one && tmp->name && strstr(tmp->name, arg_one) != NULL)
	{
	  asprintf(&buf, ":irc.localhost 322 %s %s 1 :\r\n",
		   chan->nick[fd], tmp->name);
	  circbuff_write(&(data->circbuff[fd]), buf);
	  data->circbuff_read[fd] = 1;
	}
      else if (tmp->name && arg_one == NULL)
	{
	  asprintf(&buf, ":irc.localhost 322 %s %s 1 :\r\n", chan->nick[fd],
		   tmp->name);
	  circbuff_write(&(data->circbuff[fd]), buf);
	  data->circbuff_read[fd] = 1;
	}
      tmp = tmp->next;
    }
  asprintf(&buf, ":irc.localhost 323 %s :End of /LIST\r\n", chan->nick[fd]);
  circbuff_write(&(data->circbuff[fd]), buf);
  data->circbuff_read[fd] = 1;
}
