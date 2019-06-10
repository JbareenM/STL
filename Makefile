#!make -f

all: demo
	./$<

demo:  Demo.o 
	clang++ -std=c++17 $^ -o demo

test:  Test.o 
	clang++ -std=c++17 $^ -o test

%.o: %.cpp Monom.hpp Polynom.hpp 
	clang++ -std=c++17 --compile $< -o $@

version:
	clang++ --version

clean:
	rm -f *.o demo test
