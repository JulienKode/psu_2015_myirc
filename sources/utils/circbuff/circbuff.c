/*
** circbuff.c for  in /home/karst_j/PSU_2015_myirc/sources/utils
**
** Made by Julien Kast
** Login   <karst_j@epitech.net>
**
** Started on  Wed May 18 21:29:44 2016  Julien Kast
** Last update Wed May 25 20:35:01 2016 
*/

#include	"utils_circbuff.h"
#include	<stdlib.h>

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
      data->buffer[data->wpos] = *str;
      printf("WRITE buff[%d] = [%c]\n", data->wpos, *str);
      str++;
      data->wpos++;
      if (data->wpos >= data->maxLen)
	data->wpos = 0;
    }
  data->buffer[data->wpos] = 0;
  data->wpos++;
  printf("WRITE WPOS=[%d]\n", data->wpos);
  if (data->wpos >= data->maxLen)
    data->wpos = 0;
  printf("WRITE WPOS=[%d]\n", data->wpos);
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
      printf("LEN buff[%d] = [%c]\n", data->rpos, c);
      sleep(1);
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
  printf("Read [%d]\n", len);
  tmp = malloc(len * sizeof(char));
  tmp[i] = 0;
  while (i < len && data->rpos < (data->maxLen + 1))
    {
      tmp[i] = data->buffer[data->rpos];
      printf("READPP buff[%d] = [%c]\n", data->rpos, tmp[i]);
      if (i == 0 && tmp[i] == 0)
	while (tmp[i] == 0)
	  {
	    tmp[i] = data->buffer[data->rpos++];
	    printf("READAA buff[%d] = [%c]\n", data->rpos, tmp[i]);
	  }
      else
	data->rpos++;
      printf("READ buff[%d] = [%c]\n", data->rpos, tmp[i]);
      if (data->rpos >= data->maxLen)
	data->rpos = 0;
      i++;
    }
  tmp[i + 1] = 0;
  data->rpos++;

  printf("Read RPOS=[%d]\n", data->rpos);
  if (data->rpos >= data->maxLen)
    data->rpos = 0;
  printf("Read RPOS=[%d]\n", data->rpos);
  return (tmp);
}

int main()
{
  t_circbuff	toto = circbuff_create(10);
  circbuff_write(&toto, "MaBite");
  circbuff_write(&toto, "to");
  printf("In circ buff [%s] = MaBite\n", circbuff_read(&toto));
  printf("In circ buff [%s] = to\n", circbuff_read(&toto));

  circbuff_write(&toto, "MaBite");
  circbuff_write(&toto, "tot");
  printf("In circ buff [%s] = aBite\n", circbuff_read(&toto));
  printf("In circ buff [%s] = tot\n", circbuff_read(&toto));
}
