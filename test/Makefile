
INCLUDES=-I ../src/ 
CFLAGS=-Wall -g 
CC=gcc
EXECS=test_at test_insert test_remove_at

all: $(EXECS)

%: %.c
	$(CC) ${INCLUDES} $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf $(EXECS)
