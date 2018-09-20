include config

MAKEFLAGS += --no-print-directory

PHONY   := all

all: init

	@$(foreach DIR, $(DIRS), $(MAKE) -C $(DIR) ;)

PHONY +=init

init:
	@test -d lib || mkdir lib
	@test -d include || mkdir include
	@cp $(SEM_INCLUDE)/* ./include/
	@cp $(SHM_INCLUDE)/* ./include/

PHONY +=clean

clean:
	@rm -rf lib include
	@$(foreach DIR, $(DIRS), $(MAKE) -C $(DIR) clean;)
