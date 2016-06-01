/*
** msg.c for  in /home/karst_j/PSU_2015_myirc/sources/server
**
** Made by
** Login   <karst_j@epitech.net>
**
** Started on  Mon May 30 22:48:45 2016
** Last update Mon May 30 23:06:14 2016 
*/

#include	"irc.h"

void		cmd_msg
(int fd, t_channel *chan,
 fd_set *fd_write, char *arg_one)
{
  if (arg_one && arg_one[0] == '#')
    chan_message(chan, arg_one);
  else if (arg_one)
    send_user(chan, )
  chan_message(chan, "Tu est sur le channel\r\n");
  (void) fd_write;

}
