/*
** graphic.h for graphic in /home/labarr_t/Projet/philo/inc
** 
** Made by Labarre thibault
** Login   <labarr_t@epitech.net>
** 
** Started on  Sat Mar 22 20:02:08 2014 Labarre thibault
** Last update Sat Mar 22 23:31:20 2014 Labarre thibault
*/

#ifndef GRAPHIC_H_
# define GRAPHIC_H_

#include <SDL/SDL.h>

typedef struct s_sprites
{
  SDL_Surface   *background;
  SDL_Surface   *eat;
  SDL_Surface   *rest;
  SDL_Surface   *think;
}t_sprites;

typedef struct s_window
{
  SDL_Surface	*ecran;
  t_sprites	*sprites;
}t_window;

#endif
