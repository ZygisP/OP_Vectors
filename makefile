main:
	g++ -std=c++17 -o main.exe vector.cpp
compile:
	g++ -c vector.cpp
link:
	g++ -o main.exe vector.o
del:
	rm *.o *.exe
run:
	./main