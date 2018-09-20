ifeq ($(SEM_CONFIG),1)
CC=gcc
CXX=g++

CXXFLAGS=-Werror -g -fPIC
CFLAGS=-Werror -g -fPIC

OBJ= $(patsubst %.cpp, %.o, $(wildcard *.cpp))
OBJ+= $(patsubst %.cpp, %.o, $(wildcard ./posix_sem/*.cpp))
OBJ+= $(patsubst %.cpp, %.o, $(wildcard ./system_sem//*.cpp))

INCLUDE= -I./include
LIB=

target=libsem.so

$(target):$(OBJ)
	$(CC) -shared $^ -o $@ $(LIB)
	mv $(target) ../

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDE)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	rm -rf $(OBJ) ../$(target)
else
echo:
	echo "Skip semaphore libsem.so "
endif
