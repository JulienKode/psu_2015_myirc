/*
1;2802;0c** utils_circbuff.h for  in /home/karst_j/PSU_2015_myirc/includes
**
** Made by Julien Karst
** Login   <karst_j@epitech.net>
**
** Started on  Wed May 18 21:26:09 2016 Julien Karst
** Last update Wed May 25 20:46:17 2016 
*/

#ifndef		UTILS_CIRCBUFF_H_
#define		UTILS_CIRCBUFF_H_

#include	<stdlib.h>
#include	<stdio.h>

typedef struct	s_circbuff
{
  char		*buffer;
  int		rpos;
  int		wpos;
  int		maxLen;
}		t_circbuff;

char		*circbuff_read(t_circbuff*);
int		circbuff_write(t_circbuff *, char *);
t_circbuff	circbuff_create(int);

#endif		/* UTILS_CIRCBUFF_H_ */
