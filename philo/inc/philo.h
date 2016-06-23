/*
** philo.h for philo in /home/labarr_t/Projet/philo/inc
** 
** Made by Labarre thibault
** Login   <labarr_t@epitech.net>
** 
** Started on  Sat Mar 22 19:57:58 2014 Labarre thibault
** Last update Sun Mar 23 17:28:48 2014 Labarre thibault
*/

#ifndef PHILO_H_
# define PHILO_H_

#include <SDL/SDL.h>
#include "graphic.h"

typedef enum e_condition
  {
    e_REPOSE,
    e_AREFLECHI,
    e_AMANGE
  }e_condition;

typedef struct s_philo
{
  e_condition	etat;
  int		id;
}t_philo;

t_philo		*init_philo();
void		*routine(void *);
void		init_mut();
t_window	*init_window();
int		launch_philo(t_philo *);
void		*display(void *);
SDL_Rect        get_posOfPhilo_next(int);
SDL_Rect        get_posOfPhilo(int);
void		eat(int);
void		think(int);
void		rest(int);

#endif
