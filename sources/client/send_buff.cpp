/*
** send_buff.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Sat Jun  4 16:34:17 2016
// Last update Wed Jun  8 01:15:21 2016 
*/

#include	"../../includes/irc.h"
#include	<string>

void		send_buff_client_write(t_client *client, char *str)
{
  circbuff_write(&(client->circbuff_write), str);
  client->circbuff_w = 1;
}

void		send_buff_client_read(t_client *client, char *str)
{
  char		*tmp;

  tmp = str;
  printf("Defore circbuff = %d [%s]\n", client->circbuff_r, tmp);
  while (*tmp)
    {
      if (*tmp == '\n')
	{
	  client->circbuff_r++;
	  printf("Detect backslash n circbuff++ = %d \n", client->circbuff_r);
	}
      tmp++;
    }
  printf("After circbuff = %d\n", client->circbuff_r);
  circbuff_write(&(client->circbuff_read), str);
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

static int  isPrintable(char *str)
{
    int     i;

    i = 0;
    while (*str)
    {
        if (*str >= 32 && *str <= 120)
            return (i);
        else
            i++;
        str++;
    }
    return (i);
}

char		*get_buff_read_underground(t_client *client)
{
  int		save;
  char		*str;

  save = client->circbuff_read.rpos;
  str = circbuff_read(&(client->circbuff_read));
  if (str != NULL)
    {
      if (check_conform(str) == 0)
	{
	  printf("NON CONFORM [%p]\n", str);
	  client->circbuff_read.rpos = save;
  	  return (NULL);
	}
      printf("DEBUG 1 [%p] BeforePos[%d] data[%s]\n", str, save, str);
      client->circbuff_r--;
    }
  return (str);
}
