CC = g++
FLAGS = -std=c++17 -masm=intel -fconcepts -pthread -fopenacc -fopenmp\
-ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Winline\
-Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast\
-Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo\
-Wzero-as-null-pointer-constant -Wsuggest-final-types\
-Wsuggest-final-methods -Wsuggest-override -lboost_serialization -pthread -l sqlite3

main: src/main.cpp src/Server.cpp src/Session.cpp src/PacketHandler.cpp src/Packet.cpp src/SessionHandler.cpp src/Database.cpp
	mkdir -p build
	${CC} src/main.cpp src/Server.cpp src/Session.cpp src/PacketHandler.cpp src/Packet.cpp src/SessionHandler.cpp src/Database.cpp -o build/ltype-server $(FLAGS)

clean:
	rm -r build
