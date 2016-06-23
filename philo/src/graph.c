/*
** graph.c for graph in /home/labarr_t/Projet/philo/src
** 
** Made by Labarre thibault
** Login   <labarr_t@epitech.net>
** 
** Started on  Sat Mar 22 22:21:15 2014 Labarre thibault
** Last update Sun Mar 23 17:36:04 2014 Labarre thibault
*/

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "graphic.h"
#include "philo.h"

void	*my_pause(void *arg)
{
  int           continuer;
  SDL_Event     event;

  continuer = 1;
  arg = arg;
  while (continuer == 1)
    {
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT)
        continuer = 0;
      else if (event.type == SDL_KEYDOWN)
        {
          if (event.key.keysym.sym == SDLK_ESCAPE)
	    {
	      exit(0);
	      continuer = 0;
	    }
        }
    }
  return (0);
}

void	act_etat(t_philo *philo, t_window *window, int i)
{
  SDL_Rect	pos_philo;

  pos_philo = get_posOfPhilo(philo[i].id);
  if (philo[i].etat == e_REPOSE)
    SDL_BlitSurface(window->sprites->rest, NULL, window->ecran, &pos_philo);
  else if (philo[i].etat == e_AREFLECHI)
    SDL_BlitSurface(window->sprites->think, NULL, window->ecran, &pos_philo);
  else if (philo[i].etat == e_AMANGE)
    SDL_BlitSurface(window->sprites->eat, NULL, window->ecran, &pos_philo);
}

void    aff_map(t_window *window, t_philo *philo)
{
  SDL_Rect	pos_Background;
  int		time;
  int		i;

  pos_Background.x = 0;
  pos_Background.y = 0;
  time = 0;
  i = 0;
  SDL_BlitSurface
    (window->sprites->background, NULL, window->ecran, &pos_Background);
  while (1)
    {
      while (i < 7)
	{
	  act_etat(philo, window, i);
	  i += 1;
	  SDL_Flip(window->ecran);
	}
      SDL_Flip(window->ecran);
      i = 0;
      time = time + 1;
    }
}

void	*display(void *arg)
{
  pthread_t	gere_key;
  t_window	*window;
  t_philo	*philo;

  philo = (t_philo *)arg;
  window = init_window();
  if (pthread_create(&gere_key, NULL, my_pause, arg) != 0)
    return (NULL);
  aff_map(window, philo);
  return (0);
}
