/*
** cmd_2.c for  in /home/karst_j/PSU_2015_myirc
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Sat Jun  4 19:23:47 2016
** Last update Sun Jun  5 12:26:32 2016 
*/

#include "../../includes/irc.h"

void	client_msg(t_client *client, char *nick, char *ok)
{
  char	*str;

  if (nick != NULL && ok != NULL)
    {
      asprintf(&str, "MSG %s %s\r\n", nick, ok);
      send_buff_client_write(client, str);
    }
}

void	client_quit(t_client *client, char *nick, char *ok)
{
  char	*str;

  (void) ok;
  (void) nick;
  asprintf(&str, "QUIT\r\n");
  send_buff_client_write(client, str);
}

void	client_help(t_client *client, char *nick, char *ok)
{
  (void) client;
  (void) ok;
  (void) nick;
  printf("HELP Command\n");
}

void	client_send(t_client *client, char *nick, char *ok)
{
  (void) client;
  (void) ok;
  (void) nick;
  printf("HELP Command\n");
}

void	client_accept(t_client *client, char *nick, char *ok)
{
  (void) client;
  (void) ok;
  (void) nick;
  printf("HELP Command\n");
}
