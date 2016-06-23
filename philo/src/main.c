/*
** main.c for main in /home/labarr_t/Projet/philo/src
** 
** Made by Labarre thibault
** Login   <labarr_t@epitech.net>
** 
** Started on  Sat Mar 22 19:42:56 2014 Labarre thibault
** Last update Sun Mar 23 12:33:39 2014 Labarre thibault
*/

#include <stdlib.h>
#include "graphic.h"
#include "philo.h"

int	main()
{
  t_philo	*philo;

  if ((philo = init_philo()) == NULL)
    return (-1);
  init_mut();
  launch_philo(philo);
  return (0);
}
