PROGRAM = main
OBJS = functions/game.o functions/output.o
CC = gcc
CFLAGS = -O2

$(PROGRAM): $(PROGRAM).o $(OBJS)
	$(CC) -o $(PROGRAM) $(PROGRAM).o $(OBJS) -lm

$(OBJS) $(PROGRAM).o: header.h

clean:
	rm -f *.o functions/*.o