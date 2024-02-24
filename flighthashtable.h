#ifndef FlightHASHTABLE_H
#define FlightHASHTABLE_H

#include<iostream>
#include "flightticket.h"
#include "MyList.h"
// include additional header files if needed

using namespace std;

class HashNode
{
	private:
		string key; // key = companyName+flightNumber
		Flight_Ticket value; //value with the flight ticket class object
	public:
		HashNode() // empty contructor
		{}
		HashNode(string key, Flight_Ticket value) //2 argument constructor
		{
			this->key = key;
			this->value = value;
		}
		//return key, return value
		friend class FlightHASHTABLE;
};

//=============================================================================
class FlightHASHTABLE
{
	private:
		HashList<HashNode> *buckets;				//List of Buckets, Please create your own List Class called MyList
		int size;					    //Current Size of HashTable
		int capacity;				    // Total Capacity of HashTable
	public:
		FlightHASHTABLE();	
		FlightHASHTABLE(int capacity);					//constructor
		~FlightHASHTABLE();						//destructor
		long hash(string key);						//implement and test different hash functions 
		int importCSV(string path); 			//Load all the flight-tickets from the CSV file to the HashTable
		int exportCSV(string path); 			//Export all the flight-tickets from the HashTable to a CSV file in an ascending order		
		int count_collisions();					//return the number of collisions on the HashTable
		int add(Flight_Ticket* data);			//add new flight to the HashTable
		void removeRecord (string companyName, int flightNumber);	//Delete a record with key from the hashtable
		void find(string companyName, int flightNumber);		//Find and Display records with same key entered 
		void allinday(string date);  					//Find and Display records with same day entered
		void printASC(string companyName, int flightNumber);  		//display the collisions for the entered key in an ascending order 
};

#endif
