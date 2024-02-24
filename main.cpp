#include<iostream>
#include<cstdlib>
#include<sstream>
#include <fstream>
#include <string>
#include <math.h>

#include "flighthashtable.h"
#include "flightticket.h"
#include "MyList.h"
#include "flightfunctions.h"


using namespace std;

int main(void)
{
	FlightHASHTABLE myFlightHASHTABLE(150001); // create a hash table with capacity 150001
	while(true)
	{
		listCommands();
		cout<<">";
		string user_input, command, parameter;
		getline(cin, user_input);
		stringstream sstr(user_input);
		getline(sstr, command, ' ');
		getline(sstr, parameter); // divide the input into command and parameter
		if (command == "import")
		{
			myFlightHASHTABLE.importCSV(parameter); //import a csv file into hashtable
		}
		else if (command == "export")
		{
			myFlightHASHTABLE.exportCSV(parameter); //export from hashtable to csv file
		}
		else if (command == "count_collisions")
		{
			myFlightHASHTABLE.count_collisions(); //count the collisions of the hashtable
		}
		else if (command == "add")
		{
			string CN, FN, CO, CD, ST, PR, TD, TA, DT;
			cout<<"Please enter the details of the flight-ticket: "<<endl;
			cout<<"Company Name: ";
			getline(cin, CN);
			cout<<"Flight Number: ";
			getline(cin, FN);
			cout<<"Country of Origin: ";
			getline(cin, CO);
			cout<<"Country of Destination: ";
			getline(cin, CD);
			cout<<"Stopover: ";
			getline(cin, ST);
			cout<<"Price: ";
			getline(cin, PR);
			cout<<"Time of Departure: ";
			getline(cin, TD);
			cout<<"Time of Arrival: ";
			getline(cin, TA);
			cout<<"Date: ";
			getline(cin, DT);
			Flight_Ticket* newticket = new Flight_Ticket(CN, stoi(FN), CO, CD, ST, PR, TD, TA, DT); //get input from user and store into variable then create a flight ticket object
			myFlightHASHTABLE.add(newticket); //add object into hashtable
		}
		else if (command == "delete")
		{
			string companyName;
			string flightnumber;
			stringstream ss(parameter);
			getline(ss, companyName, ',');
			getline(ss, flightnumber); //divide paramter into company name and flight number variables
			myFlightHASHTABLE.removeRecord(companyName, stoi(flightnumber)); // remove the record with the company name and flight number inputted
		}
		else if (command == "find")
		{
			string companyName;
			string flightnumber;
			stringstream ss(parameter);
			getline(ss, companyName, ',');
			getline(ss, flightnumber); 
			myFlightHASHTABLE.find(companyName, stoi(flightnumber)); // find the company name and flight number inputted
		}
		else if (command == "allinday")
		{
			myFlightHASHTABLE.allinday(parameter); //display all the flights on a specified date
		}
		else if (command == "printASC")
		{
			string companyName;
			string flightnumber;
			stringstream ss(parameter);
			getline(ss, companyName, ',');
			getline(ss, flightnumber);
			myFlightHASHTABLE.printASC(companyName, stoi(flightnumber)); //print in ascending order all the flight tickets with the company name and flight number inputted
		}
		else if (command == "exit")
		{
			exit(1); //exit the program
		}
	}
	return 0;
}





