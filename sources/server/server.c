/*
** main.c for  in /home/karst_j/PSU_2015_myirc/sources
**
** Made by Julien Karst
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 16 10:41:14 2016 Julien Karst
** Last update Sat Jun  4 17:54:09 2016
*/

#include "irc.h"

void			add_server(t_channel *chan)
{
  int			s;
  struct sockaddr_in	sin;
  int			val;

  val = 1;
  if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    exit(42);
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(chan->next->port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(s, (struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
      close(s);
      exit(42);
    }
  if (listen(s, 42) == -1)
    exit(42);
  chan->next->fd_type[s] = FD_SERVER;
  chan->next->fct_read[s] = add_client;
  data->circbuff_read[s] = 0;
}

void			init_fd_set(t_channel *chan, fd_set *fd_read,
				    fd_set *fd_write)
{
  t_channel		*tmp;
  int			i;

  tmp = found_channel_by_name(chan, "Accueil");
  FD_ZERO(fd_read);
  FD_ZERO(fd_write);
  FD_SET(3, fd_read);
  while (tmp->root == 0)
    {
      i = 0;
      while (i < MAX_FD)
	{
	  if (tmp->fd_type[i] == FD_CLIENT)
	    {
	      FD_SET(i, fd_read);
	      if (data->circbuff_read[i])
		FD_SET(i, fd_write);
	    }
	  i++;
	}
      tmp = tmp->next;
    }
}

void			fd_action(t_channel *chan, fd_set *fd_read,
				  fd_set *fd_write)
{
  t_channel		*tmp;
  int			fd_ok[MAX_FD];
  int			j;

  tmp = found_channel_by_name(chan, "Accueil");
  memset(fd_ok, 0, MAX_FD);
  while (tmp->root == 0)
    {
      j = -1;
      while (++j < MAX_FD)
	{
	  if (fd_ok[j] == 0 && tmp->fd_type[j] != FD_FREE)
	    {
	      if (FD_ISSET(j, fd_read) && (fd_ok[j] = 1))
		tmp->fct_read[j](tmp, j);
	      else if (FD_ISSET(j, fd_write) && (fd_ok[j] = 1))
		client_write(j);
	    }
	}
      tmp = tmp->next;
    }
}

t_channel		*init_channels(int port)
{
  t_channel		*chan;

  chan = init_list();
  create_channel(chan, port, "Accueil", -1);
  add_server(chan);
  data->chan = chan->next;
  return (chan);
}

int			main(int ac, char **argv)
{
  t_channel		*chan;
  fd_set		fd_read;
  fd_set		fd_write;
  t_data		main_data;

  if (ac != 2)
    {
      printf("Usage : ./server [port]\n");
      return (1);
    }
  signal(SIGINT, signal_handler);
  ac = -1;
  while (++ac < MAX_FD)
    main_data.circbuff[ac] = circbuff_create(1024);
  memset(main_data.circbuff_read, 0, MAX_FD);
  data = &main_data;
  chan = init_channels(atoi(argv[1]));
  while (42)
    {
      init_fd_set(chan, &fd_read, &fd_write);
      if (select(MAX_FD + 1, &fd_read, &fd_write, NULL, NULL) == -1)
	return (0);
      fd_action(chan, &fd_read, &fd_write);
    }
  return (0);
}
