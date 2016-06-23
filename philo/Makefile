##
## Makefile for Makefile in /home/labarr_t/rendu/PSU_2013_philo
## 
## Made by Labarre thibault
## Login   <labarr_t@epitech.net>
## 
## Started on  Mon Mar 17 09:30:22 2014 Labarre thibault
## Last update Sun Mar 23 17:28:16 2014 Labarre thibault
##

NAME	= philo

CC	= gcc

SRC	= ./src/

INC	= ./inc/

SRCS	= $(SRC)main.c \
	  $(SRC)init_window.c \
	  $(SRC)init_philo.c \
	  $(SRC)launch_philo.c \
	  $(SRC)routine.c \
	  $(SRC)get_pos.c \
	  $(SRC)action.c \
	  $(SRC)graph.c

CFLAGS	+= -Wall -Wextra -g3 -I$(INC)

OBJS	= $(SRCS:.c=.o) -lpthread -lSDL -ldl

$(NAME):	$(OBJS)
	$(CC) $(OBJS) -o $(NAME)


all: $(NAME)

clean:
	rm -rf *~
	rm -rf *.o
	rm -rf $(SRC)*~
	rm -rf $(SRC)*.o
	rm -rf $(INC)*~

fclean: clean
	rm -rf $(NAME)

re: fclean all
