include config

MAKEFLAGS += --no-print-directory

all:
	@$(foreach DIR, $(DIRS), $(MAKE) -C $(DIR) ;)
clean:
	@$(foreach DIR, $(DIRS), $(MAKE) -C $(DIR) clean;)

