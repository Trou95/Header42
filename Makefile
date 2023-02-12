NAME = HeaderReplacer
CC = c++
SRC = src/main.cpp src/HeaderReplacer.cpp src/Utils/FileService/FileService.cpp src/Entities/Header.cpp src/Utils/Logger/Logger.cpp src/Utils/Logger/LogService.cpp src/Utils/Utils.cpp
FLAGS = -Wall -Wextra -Werror -std=c++17

OBJS = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CC) -std=c++17 -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@rm -rf $(OBJS)

clean:
	rm -rf $(OBJS) $(NAME)

fclean: clean
	rm -rf $(NAME)

re: clean $(NAME)

.PHONY: clean fclean re
