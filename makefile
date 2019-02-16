CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
DRIVE_DIR=drive


all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR) 

main:  $(BUILD_DIR)/Element.o $(BUILD_DIR)/File.o $(BUILD_DIR)/Folder.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Group.o $(BUILD_DIR)/Permission.o $(BUILD_DIR)/Drive.o
	$(CC) main.cpp $(BUILD_DIR)/Drive.o $(BUILD_DIR)/Element.o $(BUILD_DIR)/File.o $(BUILD_DIR)/Folder.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Group.o $(BUILD_DIR)/Permission.o -o main.out


$(BUILD_DIR)/Drive.o: $(DRIVE_DIR)/Drive.cpp $(DRIVE_DIR)/User.hpp $(DRIVE_DIR)/Group.hpp $(DRIVE_DIR)/Element.hpp $(DRIVE_DIR)/Folder.hpp $(DRIVE_DIR)/File.hpp $(DRIVE_DIR)/ErrorException.hpp
	$(CC) -c $(DRIVE_DIR)/Drive.cpp -o $(BUILD_DIR)/Drive.o

$(BUILD_DIR)/Element.o: $(DRIVE_DIR)/Element.cpp $(DRIVE_DIR)/Permission.hpp $(DRIVE_DIR)/ErrorException.hpp
	$(CC) -c $(DRIVE_DIR)/Element.cpp -o $(BUILD_DIR)/Element.o

$(BUILD_DIR)/File.o: $(DRIVE_DIR)/File.cpp $(DRIVE_DIR)/Element.hpp
	$(CC) -c $(DRIVE_DIR)/File.cpp -o $(BUILD_DIR)/File.o

$(BUILD_DIR)/Folder.o: $(DRIVE_DIR)/Folder.cpp $(DRIVE_DIR)/Element.hpp
	$(CC) -c $(DRIVE_DIR)/Folder.cpp -o $(BUILD_DIR)/Folder.o

$(BUILD_DIR)/User.o: $(DRIVE_DIR)/User.cpp $(DRIVE_DIR)/ErrorException.hpp $(DRIVE_DIR)/Element.hpp
	$(CC) -c $(DRIVE_DIR)/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Group.o: $(DRIVE_DIR)/Group.cpp $(DRIVE_DIR)/ErrorException.hpp $(DRIVE_DIR)/User.hpp
	$(CC) -c $(DRIVE_DIR)/Group.cpp -o $(BUILD_DIR)/Group.o

$(BUILD_DIR)/Permission.o: $(DRIVE_DIR)/Permission.cpp
	$(CC) -c $(DRIVE_DIR)/Permission.cpp -o $(BUILD_DIR)/Permission.o


$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: examples/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: examples/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: examples/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/main.cpp -o $(BUILD_DIR)/main.o

myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/Drive.o $(BUILD_DIR)/User.o $(BUILD_DIR)/File.o $(BUILD_DIR)/Folder.o $(BUILD_DIR)/Element.o $(BUILD_DIR)/Group.o $(BUILD_DIR)/Permission.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/Drive.o  $(BUILD_DIR)/User.o $(BUILD_DIR)/File.o $(BUILD_DIR)/Folder.o $(BUILD_DIR)/Element.o $(BUILD_DIR)/Group.o $(BUILD_DIR)/Permission.o -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null