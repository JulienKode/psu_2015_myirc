/*
** list.c for  in /home/malot_k/Dropbox/Projets/Corewar/ASM
**
** Made by kevin malot
** Login   <malot_k@epitech.net>
**
** Started on  Wed Mar 18 16:58:42 2015 kevin malot
** Last update Fri Jun  3 20:59:42 2016
*/

#include <stdlib.h>
#include "../../includes/irc.h"

t_channel	*init_list()
{
  t_channel	*root;

  if ((root = malloc(sizeof(t_channel))) == NULL)
    exit(42);
  root->root = 1;
  root->port = 0;
  root->creator = 0;
  root->prev = root;
  root->next = root;
  root->name = NULL;
  return (root);
}

void		create_channel(t_channel *root, int port, char *name, int fd)
{
  int		i;
  t_channel	*elem;

  i = -1;
  if ((elem = malloc(sizeof(t_channel))) == NULL)
    exit(42);
  elem->root = 0;
  elem->creator = fd;
  elem->port = port;
  while (++i < MAX_FD)
    elem->circbuff[i] = circbuff_create(1024);
  memset(elem->fd_type, FD_FREE, MAX_FD);
  memset(elem->join, 0, MAX_FD);
  while (++i < MAX_FD)
    elem->circbuff[i] = circbuff_create(1024);
  i = 0;
  while (++i < MAX_FD)
    elem->circbuff_read[i] = 0;
  elem->name = strdup(name);
  elem->prev = root->prev;
  elem->next = root;
  root->prev->next = elem;
  root->prev = elem;
}

t_channel	*found_channel_by_name(t_channel *chan, char *str)
{
  t_channel	*tmp;

  if (chan == NULL)
    return (NULL);
  tmp = chan;
  while (tmp->root == 0)
    tmp = tmp->next;
  tmp = tmp->next;
  while (tmp->root == 0)
    {
      if (tmp && strcmp(tmp->name, str) == 0)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}
