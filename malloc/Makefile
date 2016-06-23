NAME	= libmy_malloc_$$HOSTTYPE.so

CC	= gcc

SRCS	= main_function.c \
	  upgrade_list.c \
	  upgrade_pointer.c

CFLAGS	= -Wall -Werror -Wextra

all:
	$(CC) $(CFLAGS) -c -fPIC main_function.c -o main_function.o
	$(CC) $(CFLAGS) -c -fPIC update_list.c -o update_list.o
	$(CC) $(CFLAGS) -c -fPIC update_pointer.c -o update_pointer.o
	$(CC) $(CFLAGS) -c -fPIC free_update_maillon.c -o free_update_maillon.o
	$(CC) $(CFLAGS) *.o -shared -o $(NAME)
	ln -s $(NAME) libmy_malloc.so
clean:
	rm -rf *.o
	rm -rf *~

fclean: clean
	rm -rf $(NAME)
	rm -rf libmy_malloc.so

re: fclean all
