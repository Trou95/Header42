NAME = HeaderReplace
SRC = src/*.cpp src/Utils/FileService/*.cpp src/Utils/*.cpp

all:
	c++ $(SRC) -std=c++17