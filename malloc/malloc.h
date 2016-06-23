#ifndef MALLOC_H_
# define MALLOC_H_

#include <stdio.h>
#include <unistd.h>

typedef struct s_block
{
  char		  use;
  size_t          nb_oct;
  struct s_block *next;
  struct s_block *prev;
}t_block;


t_block*	increase_size_free(t_block *);
int		check_good_size(size_t, t_block *);
t_block*	check_current_memory(size_t, t_block *, void *, void *);
t_block*	compar_free_place(size_t, t_block *);
int		is_in_my_list(void *, t_block *);


t_block*	refresh_list(t_block *);
t_block*	end_list(t_block *);
t_block*	add_start_block(size_t, t_block *, void *);
t_block*	put_between(t_block *, t_block *);
t_block*	put_last(t_block *, t_block *);

t_block*	update_maillon(void *, t_block *);

#endif
