# zhttp - A library for walking through memory.
NAME = zhttp
LDFLAGS =
IFLAGS = -I. -Ivendor/
CLANGFLAGS = -g -O0 -Wall -Werror -std=c99 -Wno-unused 
GCCFLAGS = -g -Wall -Werror -std=c99 -Wno-format-truncation #-Wno-unused -Wstrict-overflow -Wno-strict-aliasing -Wno-format-truncation -Wno-strict-overflow
DFLAGS = -fsanitize=address -fsanitize-undefined-trap-on-error -DDEBUG_H
#DEBUGFLAGS = -DDEBUG_H
CFLAGS = $(IFLAGS) $(CLANGFLAGS)
#CFLAGS = $(IFLAGS) $(GCCFLAGS)
CC = clang
#CC = gcc
PREFIX = /usr/local
VERSION = 0.01
SRC = zhttp.c
OBJ = zhttp.o
EXE =

main: request
main: response
	@printf '' > /dev/null

win: EXE = .exe
win: request
win: response
	@echo '' > /dev/null

install:
	cp $(NAME).[ch] /usr/local/include/

uninstall:
	echo rm -f /usr/local/include/$(NAME).[ch] 

debug: CFLAGS += $(DFLAGS)
debug: main 
	@printf '' > /dev/null

request: $(OBJ)
	$(CC) $(CFLAGS) -o request-test$(EXE) vendor/zwalker.c $(NAME).c request.c

response: $(OBJ) tests/words.o
response:
	$(CC) $(CFLAGS) -o response-test$(EXE) vendor/zwalker.c $(NAME).c tests/words.o response.c

tests/words.o: 
	$(CC) $(CFLAGS) -c tests/words.c -o tests/words.o
	
clean:
	rm -f *.o *.pdb *.ilk tests/*.o request-test response-test
