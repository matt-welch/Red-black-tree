run: main.o RBTree.o RBTree.hpp RBNode.o RBNode.hpp DLList.o DLList.hpp DLNode.o DLNode.hpp
	g++ -o run main.o RBTree.o RBNode.o DLList.o DLNode.o
	
main.o: main.cpp
	g++ -c $(CONFIG) main.cpp

RBTree.o: RBTree.cpp
	g++ -c $(CONFIG) RBTree.cpp

RBNode.o: RBNode.cpp
	g++ -c $(CONFIG) RBNode.cpp
	
DLList.o: DLList.cpp
	g++ -c $(CONFIG) DLList.cpp
	
DLNode.o: DLNode.cpp
	g++ -c $(CONFIG) DLNode.cpp

clean:
	rm -f run *.o core core.*

tidy: clean
	rm -f *.*~ *~

DEBUG_FLAGS = -g3 -ggdb -O0 -Wall -pedantic -DDEBUG
CONFIG		= -Wall -pedantic

debug: CONFIG=$(DEBUG_FLAGS)
debug: tidy run
