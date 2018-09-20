ifeq ($(SHM_CONFIG),1)
CC=gcc
CXX=g++

CXXFLAGS=-Werror -g -fPIC
CFLAGS=-Werror -g -fPIC

OBJ= $(patsubst %.cpp, %.o, $(wildcard *.cpp))
OBJ+= $(patsubst %.cpp, %.o, $(wildcard ./posix_shm/*.cpp))
#OBJ+= $(patsubst %.cpp, %.o, $(wildcard ./system_shm//*.cpp))

INCLUDE= -I./include
LIB=

target=libshm.so

$(target):$(OBJ)
	@$(CC) -shared $^ -o $@ $(LIB)
	@mv $(target) $(LIB_PATH)

%.o:%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDE)

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	@rm -rf $(OBJ)
else
echo:
	@echo "Skip share memory libshm.so"
clean:

endif
