/*
** routine.c for routine in /home/labarr_t/rendu/PSU_2013_philo
** 
** Made by Labarre thibault
** Login   <labarr_t@epitech.net>
** 
** Started on  Mon Mar 17 16:14:00 2014 Labarre thibault
** Last update Sun Mar 23 17:32:08 2014 Labarre thibault
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "philo.h"

static pthread_mutex_t	stick[7];

void		init_mut()
{
  int		i;

  i = 0;
  while (i < 7)
    {
      pthread_mutex_init(&stick[i], NULL);
      i += 1;
    }
}

void	if_rest(t_philo *philo, int right)
{
  if (pthread_mutex_trylock(&stick[philo->id]) == 0)
    {
      if (pthread_mutex_trylock(&stick[right]) == 0)
	{
	  philo->etat = e_AMANGE;
	  eat(philo->id);
	  pthread_mutex_unlock(&stick[philo->id]);
	  pthread_mutex_unlock(&stick[right]);
	}
      else
	{
	  philo->etat = e_AREFLECHI;
	  think(philo->id);
	  pthread_mutex_lock(&stick[right]);
	}
    }
  else
    {
      philo->etat = e_REPOSE;
      rest(philo->id);
    }
}

void	*routine(void *arg)
{
  t_philo	*philo;
  int		right;

  philo = (t_philo*)arg;
  right = philo->id + 1;
  if (right == 7)
    right = 0;
  while (1)
    {
      if (philo->etat == e_AREFLECHI)
	{
	  philo->etat = e_AMANGE;
	  eat(philo->id);
	  pthread_mutex_unlock(&stick[philo->id]);
	  pthread_mutex_unlock(&stick[right]);
	}
      else if (philo->etat == e_REPOSE)
	if_rest(philo, right);
      else
	{
	  philo->etat = e_REPOSE;
	  rest(philo->id);
	}
    }
  return (0);
}
