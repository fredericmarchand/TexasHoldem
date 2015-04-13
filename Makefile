all:	Card.o Player.o Game.o main.o Node.o Search.h NodeState.o
		g++ Card.o Player.o Game.o Node.o NodeState.o main.o -o app 

main.o:		
			g++ -c main.cpp -o main.o -lcilkrts -ldl -std=c++11 -fcilkplus

Card.o:		Card.h
			g++ -c Card.cpp -o Card.o

Player.o:	Player.h CardUtil.h
			g++ -c Player.cpp -o Player.o

Game.o:		Game.h Card.h Player.h
			g++ -c Game.cpp -o Game.o

Node.o:		Node.h NodeState.h
			g++ -c Node.cpp -o Node.o

NodeState.o:	NodeState.h
				g++ -c NodeState.cpp -o NodeState.o

clean:	
			rm -rf *.o app
