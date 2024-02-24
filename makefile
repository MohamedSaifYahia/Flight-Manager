Flights: FinalAssignment4.o flightfunctions.o
	g++ FinalAssignment4.o flightfunctions.o -o Flights

FinalAssignment4.o: FinalAssignment4.cpp
	g++ -c FinalAssignment4.cpp

flightfunctions.o: flightfunctions.cpp
	g++ -c flightfunctions.cpp

clean:
	rm *.o Flights