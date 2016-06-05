/*
** list.c for  in /home/karst_j/PSU_2015_myirc
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Sat Jun  4 20:51:19 2016
// Last update Sun Jun  5 16:46:07 2016 
*/

#include	<stdlib.h>
#include	"../../includes/irc.h"

t_client	*init_list_client()
{
  t_client	*root = new t_client;

  root->root = 1;
  root->prev = root;
  root->next = root;
  root->fd = 0;
  root->fd_type = FD_FREE;
  return (root);
}

void		create_client(t_client *root, int fd)
{
  t_client	*elem = new t_client;

  elem->root = 0;
  elem->next = root;
  elem->prev = root->prev;
  elem->fd_type = FD_CLIENT;
  if (fd == -2)
    elem->fd_type = FD_FREE;
  elem->circbuff_r = 0;
  elem->circbuff_w = 0;
  elem->circbuff_write = circbuff_create(1024);
  elem->circbuff_read = circbuff_create(1024);
  elem->fd = fd;
  elem->name = NULL;
  elem->ip = NULL;
  if (fd == -2)
    elem->fd = 0;
  printf("FROM %p NEW %p\n", root, elem);
  root->prev->next = elem;
  root->prev = elem;
}

t_client	*found_client_by_fd(t_client *client, int fd)
{
  t_client	*tmp;

  tmp = client;
  while (tmp->root == 0)
    tmp = tmp->next;
  tmp = tmp->next;
  while (tmp->root == 0)
    {
      if (tmp->root == 0 && tmp->fd == fd)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}
