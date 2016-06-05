/*
** send_buff.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Sat Jun  4 16:34:17 2016
// Last update Sun Jun  5 21:06:21 2016 
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

static int	check_conform(char *str)
{
  while (*str)
    {
      if (*str == '\r')
	{
	  *str = 0;
	  return (1);
	}
      str++;
    }
  return (0);
}

char		*get_buff_read_underground(t_client *client)
{
  int		save;
  char		*tmp;
  char		*str;

  tmp = NULL;
  save = client->circbuff_read.rpos;
  printf("circbuff before call%d\n", client->circbuff_read.rpos);
  str = circbuff_read(&(client->circbuff_read));
  printf("circbuff after call%d\n", client->circbuff_read.rpos);
  printf("STR[%s]\n", str);
  if (str)
    {
      tmp = strtok(strdup(str), "\n");
      printf("DEBUG %d %d str %s\n", strlen(tmp), strlen(str), tmp);
      if (check_conform(tmp) == 0)
	{
	  client->circbuff_read.rpos = save;
	  printf("circbuff end fail %d\n", client->circbuff_read.rpos);
	  return (NULL);
	}
      if (strlen(tmp) != strlen(str))
	{
	  client->circbuff_read.rpos -= (strlen(str) - strlen(tmp)) - 1;
	  client->circbuff_r = 1;
	}
      else
	client->circbuff_r = 0;
    }
  printf("circbuff end %d\n", client->circbuff_read.rpos);
  return (tmp);
}
