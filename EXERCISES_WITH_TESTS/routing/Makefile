CFLAGS = -Wall -g

.PHONY: all run-tests
all: run-tests

routing.o: routing.h
test_routing.o: routing.h
test_routing: test_routing.o routing.o 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ test_routing.o routing.o -lm

run-tests: test_routing
	./test_routing

clean:
	rm -f test_routing.o routing.o test.in test.out test.expected

veryclean: clean
	rm -f test_routing headlines

