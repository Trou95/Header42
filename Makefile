NAME = HeaderReplace
SRC = src/*.cpp src/Utils/FileService/*.cpp src/Entities/*.cpp src/Utils/*.cpp
FLAGS = -Wall -Wextra -Werror

all:
	c++ $(SRC) $(FLAGS) -std=c++17