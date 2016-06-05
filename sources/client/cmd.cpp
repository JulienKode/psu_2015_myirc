/*
** nick.c for  in /home/karst_j/PSU_2015_myirc
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Sat Jun  4 18:35:45 2016
// Last update Sun Jun  5 17:26:19 2016
*/

#include "../../includes/irc.h"

void		client_nick(t_client *client, char *nick, char *ok)
{
  char		*str;

  (void) ok;
  if (nick != NULL)
    {
      asprintf(&str, "NICK %s\r\n", nick);
      send_buff_client_write(client, str);
    }
  printf("IN NICK FD[%d] READ[%d] WRITE[%d]\n", client->fd, client->circbuff_r, client->circbuff_w);
}

void		client_list(t_client *client, char *list, char *ok)
{
  char		*str;

  (void) ok;
  if (list != NULL)
    asprintf(&str, "LIST %s\r\n", list);
  else
    asprintf(&str, "LIST\r\n");
  send_buff_client_write(client, str);
}

void		client_join(t_client *client, char *list, char *ok)
{
  char		*str;

  (void) ok;
  if (list != NULL)
    {
      asprintf(&str, "JOIN %s\r\n", list);
      send_buff_client_write(client, str);
    }
}

void		client_part(t_client *client, char *list, char *ok)
{
  char		*str;

  (void) ok;
  if (list != NULL)
    {
      asprintf(&str, "PART %s\r\n", list);
      send_buff_client_write(client, str);
    }
}

void		client_users(t_client *client, char *list, char *ok)
{
  char		*str;

  (void) ok;
  (void) list;
  asprintf(&str, "USERS\r\n");
  send_buff_client_write(client, str);
}
