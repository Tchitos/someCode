/*
** launch_philo.c for launch_philo in /home/labarr_t/Projet/philo/src
** 
** Made by Labarre thibault
** Login   <labarr_t@epitech.net>
** 
** Started on  Sat Mar 22 21:14:15 2014 Labarre thibault
** Last update Sun Mar 23 17:29:10 2014 Labarre thibault
*/

#include <unistd.h>
#include <pthread.h>
#include "philo.h"
#include "graphic.h"

int	launch_philo(t_philo *philo)
{
  pthread_t	thread_display;
  pthread_t	thread_philo[7];
  int		i;

  i = 0;
  if (pthread_create(&thread_display, NULL, display, &philo[0]) != 0)
    return (-1);
  while (i < 7)
    {
      if (pthread_create(&thread_philo[i], NULL, routine, &philo[i]) != 0)
        return (-1);
      if (i == 6)
        i = 1;
      else
        i += 2;
    }
  i = 0;
  while (i < 7)
    {
      pthread_join(thread_philo[i], NULL);
      i += 1;
    }
  return (0);
}
