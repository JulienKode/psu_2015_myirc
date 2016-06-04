/*
** writer.c for  in /home/karst_j/PSU_2015_myirc
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Fri Jun  3 20:49:32 2016
** Last update Fri Jun  3 21:43:20 2016
*/

#include	"irc.h"

void		client_write(int fd)
{
  char		*msg;
  int		res;

  printf("Debug Rpos[%d]\n", data->circbuff[fd].rpos);
  msg = circbuff_read(&(data->circbuff[fd]));
  printf("Debug Rpos[%d]\n", data->circbuff[fd].rpos);
  res = write(fd, msg, strlen(msg));
  printf("Buff [%d] [%d]\n", res, (int)strlen(msg));
  printf("Ecrit %d octets sur %d\n", res, (int)strlen(msg));
  if (res != (int)strlen(msg))
    {
      data->circbuff[fd].rpos -= (strlen(msg) - res) -1;
      data->circbuff_read[fd] = 1;
    }
  else
    data->circbuff_read[fd] = 0;
}
