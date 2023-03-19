CC=gcc
FLAGS= -Wall -O3 -std=c11

all: 
	$(CC) src/*.c src/catastring/*.c $(FLAGS) -o cata