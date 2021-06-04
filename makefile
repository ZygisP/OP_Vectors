main:
	g++ -std=c++17 -o main.exe main_vec.cpp func_vec.cpp mokinys.cpp
compile:
	g++ -c main_vec.cpp func_vec.cpp
link:
	g++ -o main.exe main_vec.o func_vec.o
del:
	rm *.o *.exe
run:
	./main