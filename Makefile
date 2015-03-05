all:	Card.o Player.o Dealer.o Game.o main.o
		g++ Card.o Player.o Dealer.o Game.o main.o -o app 

main.o:		
			g++ -c main.cpp -o main.o #-lcilkrts -ldl -std=c++11 -fcilkplus

Card.o:		Card.h
			g++ -c Card.cpp -o Card.o

Player.o:	Player.h
			g++ -c Player.cpp -o Player.o

Dealer.o:	Dealer.h
			g++ -c Dealer.cpp -o Dealer.o

Game.o:		Game.h Card.h Player.h
			g++ -c Game.cpp -o Game.o

clean:	
			rm -rf *.o app