/*
** send_buff.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Sat Jun  4 16:34:17 2016
** Last update Sun Jun  5 12:14:46 2016 
*/

#include	"../../includes/irc.h"

void		send_buff_client_write(t_client *client, char *str)
{
  circbuff_write(&(client->circbuff_write), str);
  client->circbuff_w = 1;
}

void		send_buff_client_read(t_client *client, char *str)
{
  circbuff_write(&(client->circbuff_read), str);
  client->circbuff_r = 1;
}
