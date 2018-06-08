PROG = main
CXX = g++
FLAGS = -Wall
OBJS = Voting_Algorithm.o userInput.o STV.o Plurality.o CSV_Reader.o main.o


build: $(OBJS)
	$(CXX) $(FLAGS) -o $(PROG) $(OBJS)
	
Voting_Algorithm.o: Voting_Algorithm.cpp Voting_Algorithm.h
	$(CXX) -c -o Voting_Algorithm.o Voting_Algorithm.cpp
userInput.o: userInput.cpp userInput.h
	$(CXX) -c -o userInput.o userInput.cpp
STV.o: STV.cpp STV.h
	$(CXX) -c -o STV.o STV.cpp
Plurality.o: Plurality.cpp Plurality.h
	$(CXX) -c -o Plurality.o Plurality.cpp
CSV_Reader.o: CSV_Reader.cpp CSV_Reader.h
	$(CXX) -c -o CSV_Reader.o CSV_Reader.cpp
main.o: main.cpp
	$(CXX) -c -o main.o main.cpp
	
clean:
	rm -f main $(OBJS)