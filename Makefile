all: hello chess

hello: hello.c
	gcc -Wall -Werror -o hello hello.c

chess: chess.c
	gcc -Wall -Werror -o chess chess.c

clean:
	rm hello
	rm chess

run_hello:
	./hello

run_chess:
	./chess

