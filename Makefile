NAME = HeaderReplacer
CC = c++
SRC = src/main.cpp src/HeaderReplacer.cpp src/Utils/FileService/FileService.cpp src/Entities/Header.cpp src/Utils/Logger/Logger.cpp src/Utils/Logger/LogService.cpp src/Utils/Utils.cpp
FLAGS = -Wall -Wextra -Werror -std=c++17

OBJS    = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(SRC) $(FLAGS)

clean:
	rm -rf $(OBJS) $(NAME)

fclean: clean
	rm -rf $(NAME)

re: clean $(NAME)

.PHONY: clean fclean re
