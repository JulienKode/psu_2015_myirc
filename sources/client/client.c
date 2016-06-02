/*
** main.c for  in /home/karst_j/PSU_2015_myirc/sources
**
** Made by Julien Karst
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 16 10:41:14 2016 Julien Karst
** Last update Wed Jun  1 22:17:29 2016
*/

#include "irc.h"

t_cmd                   cmds[] =
  {
    {"/server", &client_server},
    /* {"/nick", &client_nick}, */
    /* {"/list", &client_list}, */
    /* {"/join", &client_join}, */
    /* {"/part", &client_part}, */
    /* {"/users", &client_users}, */
    /* {"/msg", &client_msg}, */
    /* {"/send_file", &client_send}, */
    /* {"/accept_file", &client_accept}, */
    /* {"/help", &client_help}, */
    /* {"/quit", &client_quit}, */
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
  while (i < 1)/*CMD_CLIENT_NUMBER)*/
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
  size_t		n;

  n = 4096;
  buf = NULL;
  if ((size = getline(&buf, &n, stdin)) > 0)
    {
      buf[size - 1] = 0;
      if (buf[0] == '/')
	parse_cmd(client, buf);
      else
	dprintf(client->fd, "%s\r\n", buf);
    }
}

void			client_server(t_client *client, char *ip, char *port)
{
  struct protoent	*pe;

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

int			main()
{
  t_client		*client;
  int                   size;
  char			buf[4096];
  struct timeval tv;

  tv.tv_sec = 1;
  tv.tv_usec = 0;
  if ((client = malloc(sizeof(t_client))) == NULL)
    return (1);
  client->fd = 0;
  while (42)
    {
      FD_ZERO(&(client->fd_read));
      FD_ZERO(&(client->fd_write));
      FD_SET(0, &(client->fd_read));
      FD_SET(client->fd, &(client->fd_write));
      FD_SET(client->fd, &(client->fd_read));
      if (select(client->fd + 1, &(client->fd_read),
		 &(client->fd_write), NULL, &tv) == -1)
	return (1);
      if (FD_ISSET(0, &(client->fd_read)))
      	client_read(client);
      if (FD_ISSET(client->fd, &(client->fd_write)) && client->fd != 0)
	{
	  size = recv(client->fd, buf, 4095, MSG_DONTWAIT);
	  if (size > 0)
	    write(1, buf, size);
	}
    }
  return (0);
}
