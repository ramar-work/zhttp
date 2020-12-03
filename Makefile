# zhttp - A library for walking through memory.
NAME = zhttp 
OS = $(shell uname | sed 's/[_ ].*//')
LDFLAGS =
CLANGFLAGS = -g -O0 -Wall -Werror -std=c99 -Wno-unused -Wno-format-security -fsanitize=address -fsanitize-undefined-trap-on-error -DDEBUG_H
#GCCFLAGS = -g -Wall -Werror -std=c99 #-Wno-unused -Wstrict-overflow -Wno-strict-aliasing -Wno-format-truncation -Wno-strict-overflow 
CFLAGS = $(CLANGFLAGS)
#CFLAGS = $(GCCFLAGS)
CC = clang
#CC = gcc
PREFIX = /usr/local
VERSION = 0.01

test:
	$(CC) $(CFLAGS) -o zhttp-test zhttp.c vendor/zwalker.c main.c
