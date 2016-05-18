/*
** utils_circbuff.h for  in /home/karst_j/PSU_2015_myirc/includes
**
** Made by Julien Karst
** Login   <karst_j@epitech.net>
**
** Started on  Wed May 18 21:26:09 2016 Julien Karst
** Last update Wed May 18 21:29:28 2016 
*/

#ifndef		UTILS_CIRCBUFF_H_
#define		UTILS_CIRCBUFF_H_

typedef struct	s_circbuff
{
  char		*buffer;
  int		pos;
  int		maxLen;
}		t_circbuff;

#endif		/* UTILS_CIRCBUFF_H_ */
