/*
** send_buff.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Sat Jun  4 16:34:17 2016
** Last update Sat Jun  4 22:37:54 2016 
*/

#include	"../../includes/irc.h"

void		send_buff_client(t_client *client, char *str)
{
  circbuff_write(&(client->circbuff), str);
  client->circbuff_r = 1;
}
