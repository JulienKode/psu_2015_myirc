/*
** main.c for  in /home/karst_j/PSU_2015_myirc/sources
**
** Made by Julien Karst
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 16 10:41:14 2016 Julien Karst
** Last update Sun Jun  5 01:42:19 2016 
*/

#include "irc.h"

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
  while (i < 11)/*CMD_CLIENT_NUMBER)*/
    {
      if (cmd && strcmp(cmds[i].name, cmd) == 0)
	{
	  if (client->fd == 0 && strcmp(cmd, "/server") != 0)
	    printf("You need to be connected before doing this !\n");
	  else
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
  char			*buf;
  int			size;
  FILE			*fp;
  size_t		n;

  n = 4096;

  buf = NULL;
  fp = fdopen(client->fd, "r");
  printf("Strct %p\n", client);
  if ((size = getline(&buf, &n, fp)) > 0)
    {
      if (buf[0] == '/')
	{
	  buf[size - 1] = 0;
	  parse_cmd(client, buf);
	}
      else
	  circbuff_write(&(client->circbuff), buf);
      printf("%s\n", buf);
    }
  /*
    char			line[256];
    size = 0;
  while (fgets(line, sizeof(line), fp))
    {
      printf("Buff[%s]Line[%s]\n", buf, line);
      if (size == 0)
	asprintf(&buf, "%s", line);
      else
	asprintf(&buf, "%s%s", buf, line);
      size++;
    }
  printf("BuffFinal[%s]\n", buf);
  if (buf[0] == '/')
    parse_cmd(client, buf);
  else
    {
      buf[strlen(buf) - 1] = 0;
      printf("Get some data {%d}[%s]\n", (int)size, buf);
    }
  */
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
  FD_SET(0, fd_read);
  //  printf("INIT \n");
  while (tmp->root == 0)
    tmp = tmp->next;
  tmp = tmp->next;
  while (tmp->root == 0)
    {
      if (tmp->circbuff_r == 1)
	FD_SET(tmp->fd, fd_write);
      FD_SET(tmp->fd, fd_read);
      tmp = tmp->next;
    }
}

void			fd_action_client
(t_client *client, fd_set *fd_read, fd_set *fd_write)
{
  int			size;
  t_client		*tmp;
  FILE			*fp;
  char			*buf;
  size_t		n;

  tmp = client;
  n = 4096;
  //  printf("Action \n");
  while (tmp->root == 0)
    tmp = tmp->next;
  tmp = tmp->next;
  while (tmp->root == 0)
    {
      if (FD_ISSET(0, fd_read))
      	client_read(tmp);
      if (FD_ISSET(tmp->fd, fd_write) && tmp->fd != 0)
	{
	  printf("Action \n");
	  fp = fdopen(tmp->fd, "r");
	  size = getline(&buf, &n, fp);
	  if (size > 0)
	    write(1, buf, size);
	}
      tmp = tmp->next;
    }
}

int			main()
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
