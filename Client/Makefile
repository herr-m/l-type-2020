CC = g++
FLAGS = -g -std=c++17 -masm=intel -fconcepts -pthread -fopenacc -fopenmp\
-Wpedantic -Wall -Wextra -Wconversion -Winline\
-Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast\
-Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo\
-Wzero-as-null-pointer-constant -Wsuggest-final-types\
-Wsuggest-final-methods -Wsuggest-override -lncurses -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lboost_serialization



all: build/WindowNcurses.o build/WindowSFML.o build/Game.o build/Interface.o build/GameDisplay.o build/MenuOptions.o \
		build/Menu.o build/InputHandler.o build/Controller.o build/Connection.o build/Packet.o build/PacketHandler.o build/Session.o build/LevelMaker.o src/main.cpp buildfolder
	${CC} build/WindowNcurses.o build/WindowSFML.o build/Game.o build/Interface.o build/GameDisplay.o build/MenuOptions.o build/Menu.o \
			build/InputHandler.o build/Controller.o build/Connection.o build/Packet.o build/PacketHandler.o build/Session.o build/LevelMaker.o src/main.cpp -o build/ltype-client ${FLAGS}

build/Game.o: buildfolder
	${CC} src/Game/Game.cpp -c -o build/Game.o

build/WindowNcurses.o: src/WindowNcurses.cpp src/WindowNcurses.hpp src/WindowAbstract.hpp buildfolder
	${CC} src/WindowNcurses.cpp -c -o  build/WindowNcurses.o -lncurses -ltinfo

build/WindowSFML.o: src/WindowSFML.cpp src/WindowSFML.hpp src/WindowAbstract.hpp buildfolder
	${CC} src/WindowSFML.cpp -c -o  build/WindowSFML.o

build/Interface.o: src/Interface.cpp src/Interface.hpp src/InterfaceAbstract.hpp buildfolder
	${CC} src/Interface.cpp -c -o build/Interface.o

build/GameDisplay.o: src/Game/Game.hpp src/GameDisplay.cpp src/GameDisplay.hpp src/InterfaceAbstract.hpp buildfolder
	${CC}  src/GameDisplay.cpp -c -o build/GameDisplay.o

build/MenuOptions.o: src/MenuOptions.cpp src/MenuOptions.hpp buildfolder
	${CC} src/MenuOptions.cpp -c -o build/MenuOptions.o

build/Menu.o: src/Menu.cpp src/Menu.hpp buildfolder
	${CC} src/Menu.cpp -c -o build/Menu.o

build/InputHandler.o: src/InputHandler.cpp src/InputHandler.hpp buildfolder
	${CC} src/InputHandler.cpp -c -o build/InputHandler.o

build/Controller.o: src/Controller.cpp src/Controller.hpp buildfolder
	${CC} src/Controller.cpp -c -o build/Controller.o

build/Connection.o: src/Connection/Connection.cpp src/Connection/Connection.hpp buildfolder
	${CC} src/Connection/Connection.cpp -c -o build/Connection.o

build/Packet.o: src/Connection/Packet.cpp src/Connection/Packet.hpp buildfolder
	${CC} src/Connection/Packet.cpp -c -o build/Packet.o

build/PacketHandler.o: src/Connection/PacketHandler.cpp src/Connection/PacketHandler.hpp buildfolder
	${CC} src/Connection/PacketHandler.cpp -c -o build/PacketHandler.o

build/Session.o: src/Connection/Session.cpp src/Connection/Session.hpp buildfolder
	${CC} src/Connection/Session.cpp -c -o build/Session.o

build/LevelMaker.o: src/levelmaker/LevelMaker.cpp src/levelmaker/LevelMaker.hpp buildfolder
	${CC} src/levelmaker/LevelMaker.cpp -c -o build/LevelMaker.o

buildfolder:
	mkdir -p build
	
clean:
	rm -r build
