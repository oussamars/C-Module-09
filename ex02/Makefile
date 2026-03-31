SRCS =	PmergeMe.cpp main.cpp

CC = c++

CFLAGS = -Wall -Werror -Wextra -std=c++98

NAME = PmergeMe

OBJECTS = $(SRCS:.cpp=.o)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 

.SECONDARY: $(OBJECTS)