
main: main.cpp Drive.o Element.o File.o Folder.o User.o Group.o Permission.o
	g++ main.cpp Drive.o Element.o File.o Folder.o User.o Group.o Permission.o -o ./drive.out

Drive.o: Drive.cpp User.o Group.o Element.o Folder.o File.o ErrorException.hpp
	g++ -c Drive.cpp -o Drive.o

Element.o: Element.cpp Permission.o ErrorException.hpp
	g++ -c Element.cpp -o Element.o

File.o: File.cpp Element.o
	g++ -c File.cpp -o File.o

Folder.o: Folder.cpp Element.o
	g++ -c Folder.cpp -o Folder.o

User.o: User.cpp ErrorException.hpp
	g++ -c User.cpp -o User.o

Gruop.o: Group.cpp  ErrorException.hpp
	g++ -c Group.cpp -o Group.o

Permission.o: Permission.cpp
	g++ -c Permission.cpp -o Permission.o



clean:
	rm -rf *.o *.out