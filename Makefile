CC=gcc
FLAGS= -Wall -O3 -std=c11

all: 
	$(CC) src/std/*.c src/*.c src/catastring/*.c $(FLAGS) -o cata
