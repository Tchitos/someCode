#include "malloc.h"

static t_block	*list = NULL;
static void	*current = NULL;
static void	*max = NULL;

void	*malloc(size_t size)
{
  t_block	*new;
  size_t	tmp_size;

  if (size <= 0)
    return (NULL);
  max = sbrk(0);
  list = check_current_memory(size, list, current, max);
  list = refresh_list(list);
  max = sbrk(0);
  list = compar_free_place(size, list);
  tmp_size = list->nb_oct;
  list->use = 1;
  list->nb_oct = size;
  if (tmp_size > (size + sizeof(t_block)) || list->next == NULL)
    {
      new = (void*)(char*)list + (size + sizeof(t_block));
      new->use = 0;
      new->nb_oct = tmp_size - (size + sizeof(t_block));
      if (list->next != NULL)
	list = put_between(new, list);
      else
	list = put_last(new, list);
    }
  return ((void*)(char*)list + sizeof(t_block));
}

void	free(void *ptr)
{
  void *tmp;

  list = refresh_list(list);
  tmp = end_list(list);
  if (ptr != NULL && (void*)ptr >= (void*)list &&
      (void*)ptr <= tmp && is_in_my_list(ptr, list) == 0)
    {
      ptr = (char*)ptr - sizeof(t_block);

      list = update_maillon(ptr, list);

      if (list->prev != NULL && list->prev == 0)
	{
	  list->prev->nb_oct = list->prev->nb_oct + list->nb_oct +
	    sizeof(t_block);
	  list->prev->next = list->next;
	  list->next->prev = list->prev;
	}
      while (list->next != NULL)
      	list = list->next;
      while(list->nb_oct > (getpagesize() + sizeof(t_block) + 1))
      	{
      	  brk(sbrk(0) - getpagesize());
      	  list->nb_oct = list->nb_oct - getpagesize();
      	}
    }
}

void	*calloc(size_t nb, size_t size)
{
  char	*ptr;
  unsigned int	i;

  if (nb == 0 || size == 0)
    return (NULL);
  ptr = malloc(nb * size);
  i = 0;
  while (i < nb * size)
    {
      ptr[i] = '\0';
      i += 1;
    }
  return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
  void *new_ptr;

  if (size == 0)
    return (ptr);
  if (ptr != NULL && size == 0)
    free(ptr);
  if (ptr == NULL)
    return ((ptr = malloc(size)));
  new_ptr = malloc(size + sizeof((char*)ptr));
  free(ptr);
  return (new_ptr);
}

void	show_alloc_mem()
{
  t_block	*tmp;
  list = refresh_list(list);
  tmp = list;
  printf("break : %p\n", max);
  while (tmp != NULL)
    {
      if (tmp->use == 1)
      	printf("%p - %p : %zu octects\n",
      	       tmp, ((char*)tmp + tmp->nb_oct), tmp->nb_oct);
      tmp = tmp->next;
    }
}
