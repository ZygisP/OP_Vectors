main: func_vec.o
	g++ -std=c++17 -O3 -o main main_vec.cpp func_vec.cpp
fun:
	g++ c- func_vec.cpp
run:
	./main