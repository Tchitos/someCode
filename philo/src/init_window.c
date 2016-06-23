/*
** init_window.c for init_window in /home/labarr_t/Projet/philo/src
** 
** Made by Labarre thibault
** Login   <labarr_t@epitech.net>
** 
** Started on  Sat Mar 22 19:53:34 2014 Labarre thibault
** Last update Sun Mar 23 17:32:43 2014 Labarre thibault
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "philo.h"
#include "graphic.h"

void    load_sprites(t_window *window)
{
  window->sprites->background = SDL_LoadBMP("ressource/background.bmp");
  window->sprites->eat = SDL_LoadBMP("ressource/Eat.bmp");
  window->sprites->rest = SDL_LoadBMP("ressource/Rest.bmp");
  window->sprites->think = SDL_LoadBMP("ressource/Think.bmp");
}

t_window	*init_window()
{
  t_window	*window;

  if ((window = malloc(sizeof(*window))) == NULL)
    return (NULL);
  if ((window->sprites = malloc(sizeof(t_sprites))) == NULL)
    return (NULL);
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
      fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n",
	      SDL_GetError());
      exit(EXIT_FAILURE);
    }
  window->ecran = NULL;
  window->ecran = SDL_SetVideoMode(900, 700, 32, SDL_HWSURFACE);
  SDL_WM_SetCaption("Philosophe", NULL);
  load_sprites(window);
  return (window);
}
