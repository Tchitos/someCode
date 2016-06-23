#include "malloc.h"

t_block*	refresh_list(t_block *list)
{
  while (list->prev != NULL)
    list = list->prev;
  return (list);
}

t_block*	end_list(t_block *list)
{
  void		*ptr;
  t_block	*tmp;

  tmp = list;
  while (tmp->next != NULL)
    tmp = tmp->next;
  if (tmp->use != 0 && tmp->use != 1)
    tmp = NULL;
  while (list->next != NULL)
    list = list->next;
  ptr = (char*)list + list->nb_oct;
  return (ptr);
}

t_block		*add_start_block(size_t size_page, t_block *list, void *current)
{
  list = current;
  list->use = 0;
  list->nb_oct = size_page;
  list->next = NULL;
  list->prev = NULL;
  return (list);
}

t_block*	put_between(t_block *new, t_block *list)
{
  new->next = list->next;
  new->next->prev = new;
  new->prev = list;
  list->next = new;
  return (list);
}

t_block*	put_last(t_block *new, t_block *list)
{
  new->next = NULL;
  new->prev = list;
  list->next = new;
  return (list);
}
