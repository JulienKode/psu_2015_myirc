/*
** main.c for  in /home/karst_j/PSU_2015_myirc/sources
**
** Made by Julien Karst
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 16 10:41:14 2016 Julien Karst
** Last update Mon May 16 10:41:59 2016
*/

#include "irc.h"

t_cmd                   cmds[] =
  {
    {"/nick", &cmd_nick},
    {"/list", &cmd_list},
    {"/join", &cmd_join},
    {"/part", &cmd_part},
    {"/users", &cmd_users},
    {"/msg", &cmd_msg},
    {"/send_file", &cmd_send},
    {"/accept_file", &cmd_accept},
  };

void	cmd_nick(int fd, t_env *e, fd_set *fd_write, char *arg_one)
{
  (void) fd;
  (void) e;
  (void) fd_write;
  (void) arg_one;
}

void	cmd_list(int fd, t_env *e, fd_set *fd_write, char *arg_one)
{
  (void) fd;
  (void) e;
  (void) fd_write;
  (void) arg_one;
}

void	cmd_join(int fd, t_env *e, fd_set *fd_write, char *arg_one)
{
  (void) fd;
  (void) e;
  (void) fd_write;
  (void) arg_one;
}

void	cmd_part(int fd, t_env *e, fd_set *fd_write, char *arg_one)
{
  (void) fd;
  (void) e;
  (void) fd_write;
  (void) arg_one;
}

void	cmd_users(int fd, t_env *e, fd_set *fd_write, char *arg_one)
{
  (void) fd;
  (void) e;
  (void) fd_write;
  (void) arg_one;
}

void	cmd_msg(int fd, t_env *e, fd_set *fd_write, char *arg_one)
{
  (void) fd;
  (void) e;
  (void) fd_write;
  (void) arg_one;
}

void	cmd_send(int fd, t_env *e, fd_set *fd_write, char *arg_one)
{
  (void) fd;
  (void) e;
  (void) fd_write;
  (void) arg_one;
}

void	cmd_accept(int fd, t_env *e, fd_set *fd_write, char *arg_one)
{
  (void) fd;
  (void) e;
  (void) fd_write;
  (void) arg_one;
}

void			parse_cmd(char *buf, t_env *e, int fd, fd_set *fd_write)
{
  char			*cmd;
  char			*arg_one;
  int			i;
  int			valid;

  cmd = strtok(buf, " \t");
  arg_one = strtok(NULL, " \t");
  i = 0;
  valid = 0;
  while (i < CMD_NUMBER)
    {
      if (cmd && strcmp(cmds[i].name, cmd) == 0)
	{
	  cmds[i].p(fd, e, fd_write, arg_one);
	  valid = 1;
	}
      i++;
    }
  if (valid == 0)
    dprintf(fd, "Unknown command\n");
}

void			send_message(char *buf, t_env *e, int fd, fd_set *fd_write)
{
  int			i;

  // Il faudra également s'assurer que i est dans le même channel que fd
  for (i = 0; i < MAX_FD; i++)
    if (i != fd && e->fd_type[i] == FD_CLIENT && FD_ISSET(i, fd_write))
      dprintf(i, "%s\n", buf);
}

void			client_read(t_env *e, int fd, fd_set *fd_read,
				    fd_set *fd_write)
{
  char			*buf;
  int			size;
  size_t		n;
  FILE			*fp;

  n = 4096;
  fp = fdopen(fd, "r");
  buf = NULL;
  (void) fd_read;
  if ((size = getline(&buf, &n, fp)) > 0)
    {
      buf[size - 1] = 0;
      if (buf[0] == '/')
	  parse_cmd(buf, e, fd, fd_write);
      else
	send_message(buf, e, fd, fd_write);
    }
  else
    {
      printf("Connection closed\n");
      fclose(fp);
      close(fd);
      e->fd_type[fd] = FD_FREE;
      return;
    }
}

void			add_client(t_env *e, int s)
{
  int			cs;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;

  client_sin_len = sizeof(client_sin);
  cs = accept(s, (struct sockaddr *)&client_sin, &client_sin_len);
  e->fd_type[cs] = FD_CLIENT;
  e->fct_read[cs] = client_read;
  e->fct_write[cs] = NULL;
}

void			server_read(t_env *e, int fd, fd_set *fd_read,
				    fd_set *fd_write)
{
  (void) fd_read;
  (void) fd_write;
  add_client(e, fd);
}

void			add_server(t_env *e)
{
  int			s;
  struct sockaddr_in	sin;
  int			val;

  val = 1;
  s = socket(PF_INET, SOCK_STREAM, 0);
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(e->port);
  sin.sin_addr.s_addr = INADDR_ANY;
  bind(s, (struct sockaddr*)&sin, sizeof(sin));
  listen(s, 42);
  e->fd_type[s] = FD_SERVER;
  e->fct_read[s] = server_read;
  e->fct_write[s] = NULL;
}

int			main(int ac, char **argv)
{
  t_env			e;
  int			i;
  int			j;
  fd_set		fd_read;
  fd_set		fd_write;
  struct timeval	tv;

  if (ac == 2)
    {
      memset(e.fd_type, FD_FREE, MAX_FD);
      e.port = atoi(argv[1]);
      add_server(&e);
      tv.tv_sec = 0;
      tv.tv_usec = 0;
      while (42)
	{

	  /* Init de la liste des fd lecture */
	  FD_ZERO(&fd_read);
	  for (i = 0; i < MAX_FD; i++)
	    if (e.fd_type[i] != FD_FREE)
	      FD_SET(i, &fd_read);

	  /* Init de la liste des fd ecriture */
	  FD_ZERO(&fd_write);
	  for (i = 0; i < MAX_FD; i++)
	    if (e.fd_type[i] != FD_FREE)
	      FD_SET(i, &fd_write);

	  if (select(MAX_FD, &fd_read, &fd_write, NULL, &tv) == -1)
	    {
	      perror("select");
	      exit(42);
	    }
	  for (j = 0; j < MAX_FD; j++)
	    if (FD_ISSET(j, &fd_read))
	      e.fct_read[j](&e, j, &fd_read, &fd_write);
	}
    }
  return (0);
}
