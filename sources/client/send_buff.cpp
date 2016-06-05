/*
** send_buff.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Sat Jun  4 16:34:17 2016
** Last update Sun Jun 05 23:20:12 2016 Julien Karst
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
  char		*tmp;
  char		*str;

  tmp = NULL;
  save = client->circbuff_read.rpos;
  str = circbuff_read(&(client->circbuff_read));
  if (str)
    {
      tmp = strtok(strdup(str), "\n");
      if (isPrintable(tmp) != 0)
      {
          printf("TEST %s\n", tmp);
  	  client->circbuff_read.rpos = save + isPrintable(tmp);
      client->circbuff_r = 1;
  	  return (NULL);
      }
      if (strlen(tmp) == strlen(str))
	{
	  client->circbuff_r = 1;
	  return (NULL);
	}
      if (check_conform(tmp) == 0)
      {
  	  client->circbuff_read.rpos = save;
  	  return (NULL);
	}
      if (strlen(tmp) != strlen(str))
        {
          client->circbuff_read.rpos -= (strlen(str) - strlen(tmp)) - 1;
          client->circbuff_r = 1;
        }
      else
	client->circbuff_r = 1;
    }
  return (tmp);
}
