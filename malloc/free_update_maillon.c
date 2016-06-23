#include "malloc.h"

t_block*	update_maillon(void *ptr, t_block *list)
{
  list = (t_block*)ptr;
  list->use = 0;
  if (list->next != NULL && list->next->use == 0)
    {
      list->nb_oct = list->nb_oct + list->next->nb_oct + sizeof(t_block);
      if (list->next->next != NULL)
	{
	  list->next = list->next->next;
	  list->next->prev = list;
	}
      else
	list->next = NULL;
    }
  return (list);
}
