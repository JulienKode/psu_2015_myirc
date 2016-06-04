/*
** signal_handler.c for  in /home/karst_j/PSU_2015_myirc
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Sat Jun  4 17:25:37 2016
** Last update Sat Jun  4 17:47:40 2016 
*/

#include	"irc.h"

void		signal_handler(int dummy)
{
  int		i;
  t_channel	*tmp;

  (void) dummy;
  i = -1;
  tmp = found_channel_by_name(data->chan, "Accueil");
  if (tmp == NULL)
    return;
  while (++i < MAX_FD)
    {
      if (tmp->fd_type[i] != FD_FREE)
	{
	  close(i);
	}
    }
}
