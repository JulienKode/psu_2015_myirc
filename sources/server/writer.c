/*
** writer.c for  in /home/karst_j/PSU_2015_myirc
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Fri Jun  3 20:49:32 2016
** Last update Fri Jun  3 21:40:21 2016 
*/

#include	"irc.h"

void		client_write(t_channel *chan, int fd)
{
  char		*msg;
  int		res;

  printf("Debug Rpos[%d]\n", chan->circbuff[fd].rpos);
  msg = circbuff_read(&(chan->circbuff[fd]));
  printf("Debug Rpos[%d]\n", chan->circbuff[fd].rpos);
  res = write(fd, msg);
  printf("Buff [%d] [%d]\n", res, strlen(msg));
  if (res == strlen(msg))
    {
      chan->circbuff[fd].rpos -= (strlen(msg) - res) -1;
      chan->circbuff_read[fd] = 1;
    }
  else
    chan->circbuff_read[fd] = 0;
}
