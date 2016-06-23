#include "malloc.h"

t_block*	increase_size_free(t_block *list)
{
  while (list->next != NULL)
    list = list->next;
  list->nb_oct = list->nb_oct + getpagesize();
  return (list);
}

int	check_good_size(size_t size, t_block *list)
{
  while (list->next != NULL)
    list = list->next;
  if (list->nb_oct <= (size + sizeof(t_block)))
    return (0);
  return (1);
}

t_block*	check_current_memory
(size_t size, t_block *list, void *current, void *max)
{
  if (current == NULL ||
      ((char*)max - (char*)current) <= (long)(size + sizeof(t_block)) ||
      check_good_size(size, list) == 0)
    {
      current = sbrk(getpagesize());
      if (list == NULL)
	list = add_start_block(getpagesize() - sizeof(t_block), list, current);
      if (list != NULL)
	while (check_good_size(size, list) == 0)
	  {
	    current = sbrk(getpagesize());
	    list = increase_size_free(list);
	  }
    }
  list = refresh_list(list);
  return (list);
}

t_block*	compar_free_place(size_t size, t_block *list)
{
  t_block	*tmp;

  while (list->use != 0)
    list = list->next;
  tmp = list;
  while (tmp != NULL)
    {
      if (tmp->use == 0)
	{
	  if (tmp->nb_oct >= (size + sizeof(t_block)))
	    {
	    if (tmp->nb_oct < list->nb_oct)
	      list = tmp;
	    }
	}
      tmp = tmp->next;
    }
  return (list);
}

int	is_in_my_list(void *ptr, t_block *list)
{
  t_block	*tmp;

  list = refresh_list(list);
  tmp = list;
  while (tmp != NULL)
    {
      if ((char*)ptr - sizeof(t_block) == (char*)tmp)
	return (1);
      tmp = tmp->next;
    }
  return (0);
}
