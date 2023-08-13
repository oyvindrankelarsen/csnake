PROG=main.exe
CC=gcc
CFLAGS=-g -Wall -Werror
CFLAGS2=-O3 -Wall -Werror
DEPS = 
OBJ_CODE = 
OBJ = $(OBJ_CODE) main.o 

 
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
 
$(PROG): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


