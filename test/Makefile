CXX=g++

CXXFLAGS +=-Werror -g  $(DEFINE_CONFIG)

THREAD_TEST_PATH=./sem_shm_test/thread

OBJ= $(patsubst %.cpp, %.o, $(wildcard *.cpp))
OBJ+= $(patsubst %.cpp, %.o, $(wildcard $(THREAD_TEST_PATH)/*.cpp))


INCLUDE= -I../sem/include -I../shm/include  -I$(THREAD_TEST_PATH)

LIB= -L../ -lsem -lshm -lpthread -lrt

target=a.out

$(target):$(OBJ)
	$(CXX)  -Wl,-rpath=./ $^ -o $@ $(LIB)
	mv $(target) ../

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	rm -rf $(OBJ) ../$(target)
