
INCLUDES=-I ../src/ 
CFLAGS=-Wall -g 
CC=gcc
EXECS=test_at test_insert test_remove_at test_is_in
GIT_IGNORE=../.gitignore

all: $(EXECS)

%: %.c
	$(CC) ${INCLUDES} $(CFLAGS) $< -o $@
	@if [ ! `grep "^test/$@$$" $(GIT_IGNORE)` ]; then \
		echo "test/$@" >> $(GIT_IGNORE); \
	fi

.PHONY: clean

clean:
	rm -rf $(EXECS)
