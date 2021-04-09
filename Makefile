# zhttp - A library for walking through memory.
NAME = zhttp
OS = $(shell uname | sed 's/[_ ].*//')
LDFLAGS =
IFLAGS = -I. -Ivendor/
CLANGFLAGS = -g -O0 -Wall -Werror -std=c99 -Wno-unused -Wno-format-security
GCCFLAGS = -g -Wall -Werror -std=c99 #-Wno-unused -Wstrict-overflow -Wno-strict-aliasing -Wno-format-truncation -Wno-strict-overflow
DFLAGS = -fsanitize=address -fsanitize-undefined-trap-on-error -DDEBUG_H
#DEBUGFLAGS = -DDEBUG_H
CFLAGS = $(IFLAGS) $(CLANGFLAGS)
CFLAGS = $(IFLAGS) $(GCCFLAGS)
CC = clang
CC = gcc
PREFIX = /usr/local
VERSION = 0.01

main: request
main: response
	@printf '' > /dev/null

install:
	cp $(NAME).[ch] /usr/local/include/

uninstall:
	echo rm -f /usr/local/include/$(NAME).[ch] 

debug: CFLAGS += $(DFLAGS)
debug: main 
	@printf '' > /dev/null

request:
	$(CC) $(CFLAGS) -o request-test vendor/zwalker.c $(NAME).c request.c

response: tests/words.o
response:
	$(CC) $(CFLAGS) -o response-test vendor/zwalker.c $(NAME).c tests/words.o response.c

tests/words.o: 
	$(CC) $(CFLAGS) -c tests/words.c -o tests/words.o
	
clean:
	rm -f *.o request-test response-test
