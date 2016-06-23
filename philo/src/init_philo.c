/*
** init_philo.c for init_philo in /home/labarr_t/Projet/philo/src
** 
** Made by Labarre thibault
** Login   <labarr_t@epitech.net>
** 
** Started on  Sat Mar 22 20:31:08 2014 Labarre thibault
** Last update Sun Mar 23 12:34:02 2014 Labarre thibault
*/

#include <stdlib.h>
#include "philo.h"

t_philo		*init_philo()
{
  t_philo	*philo;
  int		i;

  if ((philo = malloc(sizeof(*philo) * 7)) == NULL)
    return (NULL);
  i = 0;
  while (i < 7)
    {
      philo[i].etat = e_REPOSE;
      philo[i].id = i;
      i += 1;
    }
  return (philo);
}
