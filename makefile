client = client
objects = client.o
FLAGS = -Wall -std=c99
test = test.txt

run: $(client)
	./client test=$(test)

all: $(client)
	./client

$(client) : $(objects)
	gcc $(FLAGS) $^ -o $@

%.o : %.c
	gcc -c $(FLAGS) $< -o $@

clean: $(client)
	rm -f $(client) $(objects)

mylib :  $(objects)
	ar crs libmylib.a *.o