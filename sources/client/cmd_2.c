/*
** cmd_2.c for  in /home/karst_j/PSU_2015_myirc
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Sat Jun  4 19:23:47 2016
** Last update Sat Jun  4 19:28:44 2016 
*/

#include "irc.h"

void	client_msg(t_client *client, char *nick, char *ok)
{
  if (nick != NULL && ok != NULL)
    dprintf(client->fd, "MSG %s %s\r\n", nick, ok);
}

void	client_quit(t_client *client, char *nick, char *ok)
{
  (void) ok;
  (void) list;
  dprintf(client->fd, "QUIT\r\n");
}

void	client_help(t_client *client, char *nick, char *ok)
{
  (void) ok;
  (void) list;
  printf("HELP Command\n");
}

void	client_send(t_client *client, char *nick, char *ok)
{
  (void) ok;
  (void) list;
  printf("HELP Command\n");
}

void	client_accept(t_client *client, char *nick, char *ok)
{
  (void) ok;
  (void) list;
  printf("HELP Command\n");
}
