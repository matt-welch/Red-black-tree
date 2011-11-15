DEBUG_FLAGS = -g3 -ggdb -O0 -Wall -pedantic

run: main.o RBTree.o RBTree.hpp RBNode.o RBNode.hpp DLList.o DLList.hpp DLNode.o DLNode.hpp
	g++ -o run main.o RBTree.o RBNode.o DLList.o DLNode.o
	
main.o: main.cpp
	g++ -c $(DEBUG_FLAGS) main.cpp

RBTree.o: RBTree.cpp
	g++ -c $(DEBUG_FLAGS) RBTree.cpp

RBNode.o: RBNode.cpp
	g++ -c $(DEBUG_FLAGS) RBNode.cpp
	
DLList.o: DLList.cpp
	g++ -c $(DEBUG_FLAGS) DLList.cpp
	
DLNode.o: DLNode.cpp
	g++ -c $(DEBUG_FLAGS) DLNode.cpp

clean:
	rm -f run *.o core core.*

tidy: clean
	rm -f *.*~ *~

