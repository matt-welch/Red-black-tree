run: main.o RBTree.o RBTree.hpp RBNode.o RBNode.hpp DLList.o DLList.hpp DLNode.o DLNode.hpp
	g++ -o run main.o RBTree.o RBNode.o DLList.o DLNode.o
	
main.o: main.cpp
	g++ -c main.cpp

RBTree.o: RBTree.cpp
	g++ -c RBTree.cpp
	
DLList.o: DLList.cpp
	g++ -c DLList.cpp
	
DLNode.o: DLNode.cpp
	g++ -c DLNode.cpp

clean:
	rm -f run *.o core core.*

tidy: clean
	rm -f *.*~ *~
