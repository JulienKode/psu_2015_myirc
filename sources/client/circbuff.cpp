/*
** circbuff.c for  in /home/karst_j/PSU_2015_myirc/sources/utils
**
** Made by Julien Kast
** Login   <karst_j@epitech.net>
**
** Started on  Wed May 18 21:29:44 2016  Julien Kast
// Last update Sun Jun  5 21:48:07 2016
*/

#include	"../../includes/utils_circbuff.h"

t_circbuff	circbuff_create(int size)
{
  t_circbuff	res;

  res.maxLen = size;
  res.rpos = 0;
  res.wpos = 0;
  const int dataSize = 1024;
  res.buffer = new char[dataSize];
  return (res);
}

int		circbuff_write(t_circbuff *data, char *str)
{
  while (*str)
    {
      data->buffer[data->wpos] = *str;
      str++;
      data->wpos++;
      if (data->wpos >= data->maxLen)
	data->wpos = 0;
    }
  data->buffer[data->wpos] = 0;
  return (1);
}

static int	circbuff_len(t_circbuff *data)
{
  int		i;
  int		len;
  char		c;

  i = data->rpos;
  c = 1;
  len = 1;
  while (c && data->rpos < (data->maxLen + 1))
    {
      c = data->buffer[data->rpos];
      if (len == 1 && c == 0)
	while (c == 0)
	  c = data->buffer[data->rpos++];
      else
	data->rpos++;
      if (data->rpos >= data->maxLen)
	data->rpos = 0;
      len++;
    }
  data->rpos = i;
  return (len);
}

char		*circbuff_read(t_circbuff *data)
{
  int		len;
  char		*tmp;
  int		i;

  i = 0;
  len = circbuff_len(data);
  const int dataSize = 1024;
  tmp = new char[dataSize];
  tmp[i] = 0;
  while (i < (len - 2) && data->rpos < (data->maxLen + 1))
    {
      tmp[i] = data->buffer[data->rpos];
      if (i == 0 && tmp[i] == 0)
	while (tmp[i] == 0)
	  tmp[i] = data->buffer[data->rpos++];
      else
	data->rpos++;
      if (data->rpos >= data->maxLen)
	data->rpos = 0;
      i++;
    }
  tmp[i + 1] = 0;
  return (tmp);
}
