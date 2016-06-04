/*
** send_buff.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Sat Jun  4 16:34:17 2016
** Last update Sat Jun  4 16:36:06 2016 
*/

#include	"irc.h"

void		send_buff(int fd, char *str)
{
  circbuff_write(&(data->circbuff[fd]), str);
  data->circbuff_read[fd] = 1;
}
