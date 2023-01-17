export CXX=g++ #compiler, change it if you don't use g++
export CXXFLAGS= -Wall -std=c++17 #compiler flags
export EXEC=main #executable name

SRC= $(wildcard *.cpp) $(wildcard */*.cpp) #all source files
OBJ= $(SRC:.cpp=.o) #all object files

ifeq ($(OS),Windows_NT)
    RMCMD = del /q
	RMCMD_REC = /s
	CDCMD = dir
	OPERATING_SYSTEM := Windows
else
    RMCMD = rm -f
	RMCMD_REC = -r
	CDCMD = cd
	OPERATING_SYSTEM := Linux
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
getch/getch.o: getch/getch.hpp getch/key.h

#html
html/html.o: html/html.hpp file/file.hpp

#menu
menu/menu.o: menu/menu.hpp utility/utility.hpp getch/getch.hpp

#utility
utility/utility.o: utility/utility.hpp


#cleaning
.PHONY: clean mrproper

clean:
	$(RMCMD) $(RMCMD_REC) *.o


mrproper: clean
	$(RMCMD) $(EXEC).*
