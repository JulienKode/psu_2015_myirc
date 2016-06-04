/*
** list.c for  in /home/karst_j/PSU_2015_myirc
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Sat Jun  4 20:51:19 2016
** Last update Sat Jun  4 23:03:51 2016 
*/

#include	<stdlib.h>
#include	"irc.h"

t_client	*init_list_client()
{
  t_client	*root;

  if ((root = malloc(sizeof(t_client))) == NULL)
    exit(42);
  root->root = 1;
  root->prev = root;
  root->next = root;
  root->fd = 0;
  root->fd_type = FD_FREE;
  return (root);
}

void		create_client(t_client *root, int fd)
{
  t_client	*elem;

  if ((elem = malloc(sizeof(t_client))) == NULL)
    exit(42);
  elem->root = 0;
  elem->next = root;
  elem->prev = root->prev;
  elem->fd_type = FD_CLIENT;
  if (fd == -2)
    elem->fd_type = FD_FREE;
  elem->circbuff_r = 0;
  elem->circbuff = circbuff_create(1024);
  elem->fd = fd;
  if (fd == -2)
    elem->fd = 0;
  printf("FROM %p NEW %p\n", root, elem);
  root->prev->next = elem;
  root->prev = elem;
}
