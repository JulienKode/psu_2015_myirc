/*
** nick.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 30 18:16:50 2016
** Last update Fri Jun  3 00:07:02 2016 
*/

#include	"irc.h"

void		cmd_nick
(int fd, t_channel *chan,
 fd_set *fd_write, char *nick)
{
  char		*msg;

  (void) fd_write;
  printf("FD = %d %p [%s]\n", fd, nick, nick);
  if (nick == NULL)
    dprintf(fd, ":irc.localhost 431 * NICK :No nickname given\r\n");
  else if (nick_exists(chan, nick))
    dprintf(fd, ":irc.localhost 433 * %s "
	    ":Nickname is already in use\r\n", nick);
  else
    {
      msg = malloc(7 + strlen(chan->nick[fd]) + strlen(nick));
      if (msg == NULL)
	exit(42);
      msg = strcpy(msg, chan->nick[fd]);
      msg = strcat(msg, " NICK ");
      msg = strcat(msg, nick);
      global_message(chan, msg);
      chan->nick[fd] = strdup(nick);
    }
}

int		nick_exists(t_channel *chan, char *nick)
{
  t_channel	*tmp;
  int		i;

  tmp = chan;
  while (tmp->root == 0)
    tmp = tmp->next;
  tmp = tmp->next;
  while (tmp->root == 0)
    {
      i = 0;
      while (i < MAX_FD)
	{
	  if (tmp->nick && tmp->nick[i] && strcmp(tmp->nick[i], nick) == 0)
	    return (1);
	  i++;
	}
      tmp = tmp->next;
    }
  return (0);
}
