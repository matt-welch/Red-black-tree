DEBUG_FLAGS = -g3 -ggdb -O0 -Wall

SOURCES = main.cpp \
          RBTree.cpp \
          DLList.cpp

run: main.o RBTree.o RBTree.hpp RBNode.o RBNode.hpp DLList.o DLList.hpp DLNode.o DLNode.hpp
	g++ -o run main.o RBTree.o RBNode.o DLList.o DLNode.o
	
main.o: main.cpp
	g++ -c -g3 -ggdb -O0 main.cpp

RBTree.o: RBTree.cpp
	g++ -c -g3 -ggdb -O0 RBTree.cpp

RBNode.o: RBNode.cpp
	g++ -c -g3 -ggdb -O0 RBNode.cpp
	
DLList.o: DLList.cpp
	g++ -c -g3 -ggdb -O0 DLList.cpp
	
DLNode.o: DLNode.cpp
	g++ -c -g3 -ggdb -O0 DLNode.cpp

clean:
	rm -f run *.o core core.*

tidy: clean
	rm -f *.*~ *~
