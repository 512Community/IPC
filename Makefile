DIRS = ./sem ./shm

all:
	$(foreach DIR, $(DIRS), $(MAKE) -C $(DIR) ;)
clean:
	$(foreach DIR, $(DIRS), $(MAKE) -C $(DIR) clean;)

