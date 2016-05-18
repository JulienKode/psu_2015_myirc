/*
** circbuff.c for  in /home/karst_j/PSU_2015_myirc/sources/utils
**
** Made by Julien Kast
** Login   <karst_j@epitech.net>
**
** Started on  Wed May 18 21:29:44 2016  Julien Kast
** Last update Wed May 18 22:43:47 2016 
*/

#include	"utils_circbuff.c"

t_circbuff	circbuff_create(int size)
{
  t_circbuff	res;

  res.maxLen = size;
  res.rpos = 0;
  res.wpos = 0;
  if ((res.buffer = malloc(size * sizeof(char))) == NULL)
    {
      res.maxLen = 0;
      perror("malloc");
    }
  return (res);
}

int		circbuff_write(t_circbuff *data, char *str)
{
  while (*str)
    {
      if ((data->wpos + 1) >= data->maxLen)
	data->wpos = 0;
      data->buffer[data->wpos] = *str;
      str++;
      data->wpos++;
    }
  if ((data->wpos + 1) >= data->maxLen)
    data->wpos = 0;
  data->buffer[data->wpos] = 0;
  data->wpos++;
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
      if ((data->rpos + 1) >= data->maxLen)
	data->rpos = 0;
      c = data->buffer[data->rpos];
      data->rpos++;
      len++;
    }
  data->rpos = i;
  return (len);
}

char		*circbuff_read(t_circbuff *data)
{
  char		*tmp;
  int		i;

  i = 0;
  tmp = malloc(circbuff_len(data) * sizeof(char));
  tmp[i] = 1;
  while (tmp[i] && data->rpos < (data->maxLen + 1))
    {
      if ((data->rpos + 1) >= data->maxLen)
	data->rpos = 0;
      tmp[i] = data->buffer[data->rpos];
      data->rpos++;
      i++;
    }
  if ((data->rpos + 1) >= data->maxLen)
    data->rpos = 0;
  tmp[i + 1] = 0;
  data->rpos++;
  return (tmp);
}
