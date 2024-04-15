CC:= gcc

PROG:= prog

INCLUDE:= -I./include/

FLAGS:= -std=c11 -Wall -Wextra -Wpedantic

C_SRC:= $(wildcard ./src/*.c ./src/**/*.c)

TARGET:= ./bin/$(PROG)

ARGS:= $(wildcard ./assets/*.jpg ./assets/*.png)

all:
	$(CC) $(C_SRC) $(INCLUDE) -o $(TARGET) && $(TARGET) $(ARGS)


val:
	valgrind -s --track-origins=yes $(TARGET) 


OUTPUT:= $(wildcard ./output/*)
clean: 
	rm $(OUTPUT)