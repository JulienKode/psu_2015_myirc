/*
** main.c for  in /home/karst_j/PSU_2015_myirc/sources
**
** Made by Julien Karst
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 16 10:41:14 2016 Julien Karst
// Last update Sun Jun  5 17:25:46 2016 
*/

#include "../../includes/irc.h"

t_cmd                   cmds[] =
  {
    {"/server", &client_server},
    {"/nick", &client_nick},
    {"/list", &client_list},
    {"/join", &client_join},
    {"/part", &client_part},
    {"/users", &client_users},
    {"/msg", &client_msg},
    {"/send_file", &client_send},
    {"/accept_file", &client_accept},
    {"/help", &client_help},
    {"/quit", &client_quit}
  };

void			parse_cmd(t_client *client, char *buf)
{
  char			*cmd;
  char			*arg_one;
  char			*arg_two;
  int			i;
  int			valid;

  cmd = strtok(buf, " \t");
  arg_one = strtok(NULL, " \t");
  arg_two = strtok(NULL, " \t");
  i = 0;
  valid = 0;
  printf("CMD [%s]\n", cmd);
  while (i < 11)/*CMD_CLIENT_NUMBER)*/
    {
      if (cmd && strcmp(cmds[i].name, cmd) == 0)
	{
	  cmds[i].p(client, arg_one, arg_two);
	  valid = 1;
	}
      i++;
    }
  if (valid == 0)
    printf("Invalid command. Type /help for more info.\n");
}

void			client_read(t_client *client)
{
  char			buf[256];
  int			size;
  //FILE			*fp;
  //  size_t		n;

  size = 1;
  //  buf = NULL;
  //  n = 4096;
  //  fp = fdopen(client->fd, "r");
  if  (size > 0)
    {
      size = (int)read(client->fd, buf, 256);
      printf("CHECK[%d][%d]", buf[size], buf[size - 1]);
      buf[size] = 0;
      printf("BIG DEbug %d\n%s\n\n", size, buf);
      if (buf[0] == '/')
	{
	  buf[size - 1] = 0;
	  parse_cmd(client, buf);
	  return;
	}
      else if (client->fd != 0)
	{
	  send_buff_client_read(client, buf);
	}
      if (buf[size - 1] == 0)
	return;
    }
}

void			client_server(t_client *tmp, char *ip, char *port)
{
  t_client		*client;
  struct protoent	*pe;

  create_client(tmp, -1);
  client = tmp;
  printf("DEBUG Base[%p] NEW[%p]\n", tmp, client);
  while (client->fd != -1)
    client = client->next;
  printf("DEBUG Base[%p] NEW[%p]\n", tmp, client);
  if (ip == NULL)
    printf("Usage : /server ip [port]\n");
  else
    {
      if (strcmp(ip, "localhost") == 0)
	ip = strdup("127.0.0.1");
      client->ip = strdup(ip);
      if (port == NULL)
	{
	  printf("Use Default port : 4242\n");
	  port = strdup("4242");
	}
      client->sin.sin_family = AF_INET;
      client->sin.sin_port = htons(atoi(port));
      client->sin.sin_addr.s_addr = inet_addr(ip);
      if ((pe = getprotobyname("TCP")) == 0 ||
	  (client->fd = socket(PF_INET, SOCK_STREAM, pe->p_proto)) == -1)
	exit(42);
      client->len = sizeof(client->sin);
      if (connect(client->fd, (struct sockaddr *)&(client->sin), client->len) == -1)
	{
	  printf("Can't establish connection to %s:%s\n", ip, port);
	  close(client->fd);
	  client->fd = 0;
	  client->fd_type = FD_FREE;
	  return;
	}
    }
}

void			init_fd_set_client
(t_client *client, fd_set *fd_read, fd_set *fd_write)
{
  t_client		*tmp;

  tmp = client;
  FD_ZERO(fd_read);
  FD_ZERO(fd_write);
  while (tmp->root == 0)
    tmp = tmp->next;
  tmp = tmp->next;
  while (tmp->root == 0)
    {
      if (tmp->fd_type != FD_FREE)
	{
	  if (tmp->circbuff_w == 1)
	    FD_SET(tmp->fd, fd_write);
	  FD_SET(tmp->fd, fd_read);
	}
      tmp = tmp->next;
    }
}

void			fd_action_client
(t_client *client, fd_set *fd_read, fd_set *fd_write)
{
  int			size;
  t_client		*tmp;
  char			*buf;

  tmp = client;
  //  printf("Action \n");
  while (tmp->root == 0)
    tmp = tmp->next;
  tmp = tmp->next;
  while (tmp->root == 0)
    {
      if (FD_ISSET(tmp->fd, fd_read))
      	client_read(tmp);
      if (FD_ISSET(tmp->fd, fd_write) && tmp->fd != 0)
	{
	  printf("Cricbuff Write FD[%d]\n", tmp->fd);
	  printf("FD[%d] READ[%d] WRITE[%d]\n", tmp->fd, tmp->circbuff_r, tmp->circbuff_w);
	  buf = circbuff_read(&(tmp->circbuff_write));
	  if (buf)
	    {
	      size = (int)write(tmp->fd, buf, strlen(buf));
	      if (size != (int)strlen(buf))
		{
		  tmp->circbuff_write.rpos -= (strlen(buf) - size) - 1;
		  tmp->circbuff_w = 1;
		}
	      else
		tmp->circbuff_w = 0;
	    }
	  printf("FD[%d] READ[%d] WRITE[%d]\n", tmp->fd, tmp->circbuff_r, tmp->circbuff_w);
	}
      tmp = tmp->next;
    }
}

int			main_loop()
{
  t_client		*client;
  fd_set		fd_read;
  fd_set		fd_write;
  struct timeval	tv;

  tv.tv_sec = 1;
  tv.tv_usec = 0;
  client = init_list_client();
  create_client(client, -2);
  printf("Strct Client main %p\n", client);
  while (42)
    {
      init_fd_set_client(client, &fd_read, &fd_write);
      if (select(MAX_FD + 1, &(fd_read),
		 &(fd_write), NULL, &tv) == -1)
	return (1);
      fd_action_client(client, &fd_read, &fd_write);
    }
  return (0);
}
