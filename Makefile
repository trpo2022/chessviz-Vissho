CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -MMD

all: main.o chessviz.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

chessviz.o: libchessviz/chessviz.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

-include main.d chessviz.d

clean:
	rm ./main

run:
	./main

