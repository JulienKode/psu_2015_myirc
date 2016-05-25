/*
1;2802;0c** list.c for  in /home/malot_k/Dropbox/Projets/Corewar/ASM
**
** Made by kevin malot
** Login   <malot_k@epitech.net>
**
** Started on  Wed Mar 18 16:58:42 2015 kevin malot
** Last update Tue Apr  7 14:03:59 2015 kevin malot
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
  root->prev = root;
  root->next = root;
  root->name = NULL;
  return (root);
}

void		create_channel(t_channel *root, int port, char *name)
{
  t_channel	*elem;

  if ((elem = malloc(sizeof(t_channel))) == NULL)
    exit(42);
  elem->root = 0;
  elem->port = port;
  memset(elem->fd_type, FD_FREE, MAX_FD);
  root->name = strdup(name);
  elem->prev = root->prev;
  elem->next = root;
  root->prev->next = elem;
  root->prev = elem;
}
