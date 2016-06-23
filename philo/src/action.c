/*
** action.c for action in /home/labarr_t/Projet/philo/src
** 
** Made by Labarre thibault
** Login   <labarr_t@epitech.net>
** 
** Started on  Sun Mar 23 17:27:43 2014 Labarre thibault
** Last update Sun Mar 23 17:29:28 2014 Labarre thibault
*/

#include <unistd.h>
#include <stdio.h>

void	eat(int id)
{
  printf("Philosode %d mange.\n", id);
  sleep(3);
}

void	think(int id)
{
  printf("Philosode %d réfléchit.\n", id);
  sleep(5);
}

void	rest(int id)
{
  printf("Philosode %d se repose.\n", id);
  sleep(8);
}
