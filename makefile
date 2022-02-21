CC = gcc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -I./include

PTHREAD_LIB = -lpthread

NAME = philo

SRC_PATH =	main.c			\
			create_philo.c	\

SRC = $(addprefix src/,$(SRC_PATH))

OBJ	= $(SRC:.c=.o)

all : $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

$(NAME) : $(OBJ)
	$(CC) -o $(NAME) $(SRC) $(PTHREAD_LIB)

re : fclean all

.PHONY : all clean re