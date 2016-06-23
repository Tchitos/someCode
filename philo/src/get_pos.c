/*
** get_pos.c for philo in /home/labarr_t/Projet/philo/src
** 
** Made by Labarre thibault
** Login   <labarr_t@epitech.net>
** 
** Started on  Sun Mar 23 14:25:47 2014 Labarre thibault
** Last update Sun Mar 23 14:27:03 2014 Labarre thibault
*/

#include <SDL/SDL.h>
#include "graphic.h"
#include "philo.h"

SDL_Rect        get_posOfPhilo_next(int id)
{
  SDL_Rect	pos_philo;

  if (id == 3)
    {
      pos_philo.x = 390;
      pos_philo.y = 620;
    }
  else if (id == 4)
    {
      pos_philo.x = 140;
      pos_philo.y = 580;
    }
  else if (id == 5)
    {
      pos_philo.x = 10;
      pos_philo.y = 400;
    }
  else if (id == 6)
    {
      pos_philo.x = 150;
      pos_philo.y = 60;
    }
  return (pos_philo);
}

SDL_Rect        get_posOfPhilo(int id)
{
  SDL_Rect	pos_philo;

  if (id == 0)
    {
      pos_philo.x = 400;
      pos_philo.y = 20;
    }
  else if (id == 1)
    {
      pos_philo.x = 670;
      pos_philo.y = 70;
    }
  else if (id == 2)
    {
      pos_philo.x = 660;
      pos_philo.y = 565;
    }
  else
    return (get_posOfPhilo_next(id));
  return (pos_philo);
}
