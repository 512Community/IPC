CXX=g++

CXXFLAGS +=-Werror -g

THREAD_TEST_PATH=./sem_shm_test/thread

OBJ= $(patsubst %.cpp, %.o, $(wildcard *.cpp))
OBJ+= $(patsubst %.cpp, %.o, $(wildcard $(THREAD_TEST_PATH)/*.cpp))


INCLUDE= -I../include -I$(THREAD_TEST_PATH)

LIB= -L$(LIB_PATH) -lpthread -lrt

ifeq ($(SHM_CONFIG),1)
LIB+=-lshm
CXXFLAGS += $(DEFINE_CONFIG)
endif
ifeq ($(SEM_CONFIG),1)
LIB+=-lsem
endif
ifeq ($(LOG_CONFIG),1)
LIB+=-lmsg_log
endif

target=a.out

$(target):$(OBJ)
	@$(CXX)  -Wl,-rpath=./lib $^ -o $@ $(LIB)
	@mv $(target) ../

%.o:%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	@rm -rf $(OBJ) ../$(target)
