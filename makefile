COMPILER = g++
CFLAGS = -std=c++11 -Iinclude -c
LFLAGS = 
EXECUTABLE = bin/Release/begcar
OBJECTS = obj/Release/src/cell.o obj/Release/src/rule.o obj/Release/src/simulation.o obj/Release/src/filenotfoundexception.o obj/Release/main.o
FILES = src/cell.cpp src/rule.cpp src/simulation.cpp src/filenotfoundexception.cpp
$(EXECUTABLE): $(OBJECTS)
	$(COMPILER) $(OBJECTS) -o $(EXECUTABLE)
	ln $(EXECUTABLE) begcar
obj/Release/src/cell.o: src/cell.cpp
	$(COMPILER) $(CFLAGS) src/cell.cpp -o obj/Release/src/cell.o
obj/Release/src/rule.o: src/rule.cpp
	$(COMPILER) $(CFLAGS) src/rule.cpp -o obj/Release/src/rule.o
obj/Release/src/simulation.o: src/simulation.cpp
	$(COMPILER) $(CFLAGS) src/simulation.cpp -o obj/Release/src/simulation.o
obj/Release/src/filenotfoundexception.o: src/filenotfoundexception.cpp
	$(COMPILER) $(CFLAGS) src/filenotfoundexception.cpp -o obj/Release/src/filenotfoundexception.o
obj/Release/main.o: main.cpp
	$(COMPILER) $(CFLAGS) main.cpp -o obj/Release/main.o
clear:
	rm -f bin/Release/begcar obj/Release/main.o obj/Release/src/* begcar