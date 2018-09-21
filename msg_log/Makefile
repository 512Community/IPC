ifeq ($(SHM_CONFIG),1)
CC=gcc
CXX=g++

CFLAGS=-Werror -g -fPIC  $(DEFINE_CONFIG)

OBJ+= $(patsubst %.c, %.o, $(wildcard ./msg_log/*.c))

INCLUDE= -I./include
LIB=

target=liblog.so

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
	@echo "Skip msg log liblog.so "
clean:
endif
