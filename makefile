export CXX=g++ #compiler, change it if you don't use g++
export CXXFLAGS= -Wall -std=c++17 #compiler flags

SRC= $(wildcard *.cpp) $(wildcard */*.cpp) #all source files
OBJ= $(SRC:.cpp=.o) #all object files

ifeq ($(OS),Windows_NT)
    RMCMD = del 
	CDCMD = dir
	OPERATING_SYSTEM := Windows
	export EXEC = main.exe
else
    RMCMD = rm -f
	CDCMD = cd
	OPERATING_SYSTEM := Linux
	export EXEC = main.out
endif

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)


	
#dependencies
main: $(wildcard *.hpp) $(wildcard */*.hpp) #recompile if headers change

#agenda
agenda/agenda.o: agenda/agenda.hpp datetime/datetime.hpp datetime/data.hpp file/file.hpp utility/utility.hpp html/html.hpp

#datetime
datetime/datetime.o: datetime/datetime.hpp datetime/data.hpp datetime/deltatime.hpp
datetime/deltatime.o: datetime/data.hpp datetime/deltatime.hpp

#file
file/file.o: file/file.hpp utility/utility.hpp

#getch
getkey/getkey.o: getkey/getkey.hpp getkey/key.h

#html
html/html.o: html/html.hpp file/file.hpp

#menu
menu/menu.o: menu/menu.hpp utility/utility.hpp getkey/getkey.hpp

#utility
utility/utility.o: utility/utility.hpp


#cleaning
.PHONY: clean mrproper

clean:
	$(RMCMD)*.o
	$(RMCMD)*/*.o


mrproper: clean
	$(RMCMD) $(EXEC)
