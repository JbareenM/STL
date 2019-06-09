#!make -f

all: demo
	./$<

demo:  Demo.o 
	clang++-5.0 -std=c++17 $^ -o demo

test:  Test.o 
	clang++-5.0 -std=c++17 $^ -o test

%.o: %.cpp Monom.hpp Polynom.hpp function.hpp Monom_Comperator.hpp cont_function.hpp 
	clang++-5.0 -std=c++17 --compile $< -o $@

version:
	clang++ --version

clean:
	rm -f *.o demo test
