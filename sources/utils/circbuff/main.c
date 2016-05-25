/*
** main.c for  in /home/karst_j/PSU_2015_myirc/sources/utils
**
** Made by Julien Karst
** Login   <karst_j@epitech.net>
**
** Started on  Wed May 25 16:52:24 2016 Julien Karst
** Last update Wed May 25 20:44:56 2016 
*/

#include "utils_circbuff.h"

int main()
{
  t_circbuff toto = circbuff_create(10);
  circbuff_write(&toto, "MaBite");
  circbuff_write(&toto, "to");
  printf("In circ buff [%s] = MaBite\n", circbuff_read(&toto));
  printf("In circ buff [%s] = to\n", circbuff_read(&toto));

  circbuff_write(&toto, "MaBite");
  circbuff_write(&toto, "tot");
  printf("In circ buff [%s] = aBite\n", circbuff_read(&toto));
  printf("In circ buff [%s] = tot\n", circbuff_read(&toto));
}
