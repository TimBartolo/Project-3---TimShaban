output: TreeDr.o TreeType.o QueType.o
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors TreeDr.o TreeType.o QueType.o -o output

TreeDr.o: TreeDr.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c TreeDr.cpp

TreeType.o: TreeType.cpp TreeType.h
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c TreeType.cpp

QueType.o: QueType.cpp QueType.h
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c QueType.cpp

clean:
	rm *.o output