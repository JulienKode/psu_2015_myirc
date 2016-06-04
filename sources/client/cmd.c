/*
** nick.c for  in /home/karst_j/PSU_2015_myirc
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Sat Jun  4 18:35:45 2016
** Last update Sat Jun  4 19:23:27 2016 
*/

#include "irc.h"

void		client_nick(t_client *client, char *nick, char *ok)
{
  (void) ok;
  if (nick != NULL)
    dprintf(client->fd, "NICK %s\r\n", nick);
}

void		client_list(t_client *client, char *list, char *ok)
{
  (void) ok;
  if (list != NULL)
    dprintf(client->fd, "LIST %s\r\n", list);
  else
    dprintf(client->fd, "LIST\r\n");
}

void		client_join(t_client *client, char *list, char *ok)
{
  (void) ok;
  if (list != NULL)
    dprintf(client->fd, "JOIN %s\r\n", list);
}

void		client_part(t_client *client, char *list, char *ok)
{
  (void) ok;
  if (list != NULL)
    dprintf(client->fd, "PART %s\r\n", list);
}

void		client_users(t_client *client, char *list, char *ok)
{
  (void) ok;
  (void) list;
  dprintf(client->fd, "USERS\r\n");
}
