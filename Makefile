HEADER=server.hpp
CC=c++
FLAGS= -std=c++98 -Wall -Wextra -Werror

SRCS=main.cpp server.cpp helper_func.cpp split.cpp
OBJS=$(SRCS:.cpp=.o)
NAME=IRC

all:$(NAME)

$(NAME):$(OBJS) $(HEADER)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o:%.cpp $(HEADER)
			$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	
fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME) clean
.PHONY: all $(NAME) clean fclean re