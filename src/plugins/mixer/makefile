# Author: Martin Schwarz
# Makefile for plugin

CC=g++
CFLAGS=-g -Wall -Werror -I../include -fPIC -shared -std=c++11
NAME=Mixer

Debug: plugin
Release: plugin
all: plugin

plugin: tmpobj.o
	mkdir -p deploy
	${CC} ${CFLAGS} -o $(NAME).so *.o ${LIBS}
	mv $(NAME).so deploy/$(NAME).so

tmpobj.o: *.cpp
	${CC} ${CFLAGS} -c `find ../include -type f -name "*.cpp"` $(NAME).cpp ${LIBS}

clean:
	rm -f *.o deploy/${NAME}
