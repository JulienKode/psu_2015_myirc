/*
** list.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 30 22:35:33 2016
** Last update Sat Jun  4 15:56:16 2016
*/

#include	"irc.h"

void		cmd_list_loop(t_channel *chan, t_channel *tmp, int fd, char *a)
{
  char		*buf;

  if (a && tmp->name && tmp->name[0] == '#' && strstr(tmp->name, a))
    {
      asprintf(&buf, ":irc.localhost 322 %s %s %d :\r\n",
	       chan->nick[fd], tmp->name, nb_of_users(tmp));
      circbuff_write(&(data->circbuff[fd]), buf);
      data->circbuff_read[fd] = 1;
    }
  else if (tmp->name && tmp->name[0] == '#' && a == NULL)
    {
      asprintf(&buf, ":irc.localhost 322 %s %s %d :\r\n", chan->nick[fd],
	       tmp->name, nb_of_users(tmp));
      circbuff_write(&(data->circbuff[fd]), buf);
      data->circbuff_read[fd] = 1;
    }
}

void		cmd_list(int fd, t_channel *chan, char *arg_one)
{
  t_channel	*tmp;
  char		*buf;

  tmp = chan;
  while (tmp->root == 0)
    tmp = tmp->next;
  tmp = tmp->next;
  asprintf(&buf, ":irc.localhost 321 %s Channel :Users  Name\r\n",
	   chan->nick[fd]);
  circbuff_write(&(data->circbuff[fd]), buf);
  data->circbuff_read[fd] = 1;
  while (tmp->root == 0)
    {
      cmd_list_loop(chan, tmp, fd, arg_one);
      tmp = tmp->next;
    }
  asprintf(&buf, ":irc.localhost 323 %s :End of /LIST\r\n", chan->nick[fd]);
  circbuff_write(&(data->circbuff[fd]), buf);
  data->circbuff_read[fd] = 1;
}
