#include "MyList.h"
#include "flightticket.h"
#include "flighthashtable.h"
#include "flightfunctions.h"
#include <math.h>

void listCommands()
{
	cout<<"\n----------------------------------"<<endl;
	cout<<"import <path>      	:Import flight-tickets from a CSV file"<<endl
		<<"export <path>      	:Export flight-tickets to a CSV file"<<endl
		<<"count_collisions   	:Print Number of Collisions"<<endl
		<<"add                	:Add a new flight-ticket"<<endl
		<<"delete <key>       	:Delete a flight-ticket"<<endl
		<<"find <key>         	:Find a flight-ticket's details"<<endl
		<<"allinday <date>    	:Display all flight-tickets in a day"<<endl
		<<"printASC <key>     	:Print flight-tickets in ascending order"<<endl
		<<"exit               	:Exit the program"<<endl;
}

template <typename T>
HashList<T>::HashList() //constructor for the doubly linked list
{
    this->head = new Node<T>();
	this->tail = new Node<T>();
    this->head -> next = tail;
    this->tail -> prev = head;
}
//============================================================
template <typename T>
HashList<T>::~HashList () // destructor to clean up all nodes
{
	//todo
    while (!empty()) removeFront();

}
//============================================================

template<typename T>
int HashList<T>::size() //return size of list
{
	return listsize;
}
template <typename T>
void HashList<T>::addBefore(Node<T> *ptr, const T& elem) //add an element before a specified node
{
	//todo
	Node<T> *tmp = new Node<T>(elem);
	tmp->next = ptr;
	tmp->prev = ptr->prev;
	ptr->prev->next = tmp;
	ptr->prev=tmp; 
}
//============================================================
template <typename T>
void HashList<T>::addBack(const T& elem) // add to Back of the list
{
	//todo
	if (listsize > 0)
	{
		addBefore(this->tail, elem); 
		listsize++; //increment the size of the list as you add
	}
	else
	{
		addBefore(this->tail, elem); 
		listsize = 1;
	}
	
}

template<typename T>
void HashList<T>::remove(Node<T>* v) //remove the node v
{
	Node<T>* u = v->prev;
	Node<T>* w = v->next;
	u->next = w;
	w->prev = u;
	delete v;
	listsize--; //decrement the size of the list as you remove
}
template <typename T>
bool HashList<T>::empty() const // is list empty?
{
	return this->head->next == tail;
}
template <typename T>
void HashList<T>::removeFront() // remove front item from list
{
	if(!empty())
	{
		Node<T> *tmp = this->head->next;
		this->head->next = tmp->next;
		tmp->next->prev = head;
		delete tmp;
		listsize--; //decrement the size of the list as you remove
	}
}
//============================================================
Flight_Ticket::Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date) //assign variables to the flight-ticket object
{
	this->companyName = companyName;
	this->flightNumber = flightNumber;
	this->country_of_origin = country_of_origin;
	this->country_of_destination = country_of_destination;
	this->stopOver = stopOver;
	this->price = price;
	this->time_of_departure = time_of_departure;
	this->time_of_arrival = time_of_arrival;
	this->date = date;
}

FlightHASHTABLE::FlightHASHTABLE(int capacity)
{
	buckets = new HashList<HashNode>[capacity];	  //Array of a list/chain
	this->capacity = capacity; //capacity of the bucket
	this->size = 0; //initial size of the hashtable 
}
FlightHASHTABLE::FlightHASHTABLE() //empty constructor
{}

FlightHASHTABLE::~FlightHASHTABLE() //destructor for the hashtable
{
	delete[] buckets;
}

long FlightHASHTABLE::hash(string key) //hash function to generate a hash key
{
	size_t hashcode;
    for(int i = 0; i < key.length(); ++i) {
        hashcode += key[i] * (int)pow(31, i);
    }
    return hashcode%capacity;
}

int FlightHASHTABLE::importCSV(string path) 
{
	int imported = 0; //store the number of imported flight tickets
    string CN, tempFN, CO, CD, ST, PR, TD, TA, DT, Fline, key;
	int FN;
	ifstream Ffile(path);
	while (getline(Ffile, Fline)) //reads every line
	{
		stringstream ss(Fline);
        getline(ss, CN, ',');
		if (CN == "companyName")
		{
			continue; //skips the first line containing the example
		}
        getline(ss, tempFN, ',');
        getline(ss, CO, ',');
        getline(ss, CD, ',');
        getline(ss, ST, ',');
		getline(ss, PR, ',');
		getline(ss, TD, ',');
		getline(ss, TA, ',');
		getline(ss, DT,'\r');
		FN = stoi(tempFN); //converts the flight number to an integer
		Flight_Ticket* newticket = new Flight_Ticket(CN, FN, CO, CD, ST, PR, TD, TA, DT); //generates a flight ticket object from the csv line
		add(newticket); //adds flight ticket object to the hash table
		imported++; //increments the imported integer
	}
	cout<<imported<<endl; //print the number of imported flight tickets
	return imported;
}

int FlightHASHTABLE::add(Flight_Ticket *data)
{
	string key;
	key = data->companyName + to_string(data->flightNumber); //generate the key from the company name and flight number
	long index = hash(key); //store the hashkey of the key
	HashNode flightnode = HashNode(key, *data); //create a hashnode with the key and data of the flight ticket
	buckets[index].addBack(flightnode); //adds the hashnode to the list in the buckets index of the hash key
	size++; //increment the size of the hashtable
	return 1;
}

void FlightHASHTABLE::removeRecord(string companyName, int flightNumber)
{
	int i = 1;
	string key;
	key = companyName + to_string(flightNumber);
	long index = hash(key);
	cout<< buckets[index].size()<< " records found: "<<endl; //print the records found
	for (HashList<HashNode> :: iterator it = buckets[index].begin(); it != buckets[index].end(); ++it) //loop through the bucket at index index
	{
		cout<<i<<". "<<it.operator*().value.companyName<<','<<it.operator*().value.flightNumber<<','<<it.operator*().value.country_of_origin<<','<<it.operator*().value.country_of_destination<<','<<it.operator*().value.stopOver<<','<<it.operator*().value.price<<','<<it.operator*().value.time_of_departure<<','<<it.operator*().value.time_of_arrival<<','<<it.operator*().value.date<<endl; //print the found records 
		i++;
	}
	cout<<"Please select the record you want to delete: ";
	int choice;
	cin >> choice;
	int k = 1;
	for (HashList<HashNode> :: iterator it = buckets[index].begin(); it != buckets[index].end(); ++it)
	{
		if (k == choice) //compares the choice to an incrementing integer and loops until found 
		{
			buckets[index].remove(it.getkey()); //remove the node at the position k
			cout<<"The flight-ticket record has been successfully deleted!"<<endl;
		}
		k++;
	}
}

void FlightHASHTABLE::find(string companyName, int flightNumber)
{
	int i = 1;
	string key;
	key = companyName + to_string(flightNumber);
	long index = hash(key);
	cout<< buckets[index].size()<< " records found: "<<endl; //prints the records found
	for (HashList<HashNode> :: iterator it = buckets[index].begin(); it != buckets[index].end(); ++it) //loops through the bucket at index index
	{
		if (companyName == it.operator*().value.companyName && flightNumber == it.operator*().value.flightNumber) //if the flight number and company name match, then print records
		{
			cout<<i<<". Company Name: "<<it.operator*().value.companyName<<endl;
			cout<<"Flight Number: "<<it.operator*().value.flightNumber<<endl;
			cout<<"Country of Origin: "<<it.operator*().value.country_of_origin<<endl;
			cout<<"Country of Destination: "<<it.operator*().value.country_of_destination<<endl;
			cout<<"Stopover: "<<it.operator*().value.stopOver<<endl;
			cout<<"Price: "<<it.operator*().value.price<<endl;
			cout<<"Time of Departure: "<<it.operator*().value.time_of_departure<<endl;
			cout<<"Time of Arrival: "<<it.operator*().value.time_of_arrival<<endl;
			cout<<"Date: "<<it.operator*().value.date<<endl;
			i++; 
		}
	}
}

void FlightHASHTABLE::allinday(string date)
{
	int recordsfound = 0;
	for (int i = 0; i < capacity; i++)
	{
		for (HashList<HashNode> :: iterator it = buckets[i].begin(); it != buckets[i].end(); ++it)
		{
			if (it.operator*().value.date == date)
			{
				recordsfound++; //loops through the entire hash table and then each bucket to store the total number of records found matching the date
			}
		}
	}
	int k = 1;
	cout << recordsfound<< " records found: "<<endl;
	for (int i = 0; i < capacity; i++)
	{
		for (HashList<HashNode> :: iterator it = buckets[i].begin(); it != buckets[i].end(); ++it)
		{
			if (it.operator*().value.date == date)
			{
				cout<<k<<". "<<it.operator*().value.companyName<<','<<it.operator*().value.flightNumber<<','<<it.operator*().value.country_of_origin<<','<<it.operator*().value.country_of_destination<<','<<it.operator*().value.stopOver<<','<<it.operator*().value.price<<','<<it.operator*().value.time_of_departure<<','<<it.operator*().value.time_of_arrival<<','<<it.operator*().value.date<<endl; //prints the records found
				k++;
			}
		}
	}
}

int FlightHASHTABLE::count_collisions()
{
	int collisions = 0;
	int big = 1; //size of the array where we store keys
	int index = 0; //index of the array where we store keys
	bool inarray = false; //bool to check if a key is already in the array or not
	for (int i = 0; i < capacity; i++) // loops through the buckets array
	{
		if (buckets[i].size() > 1) //checks if a bucket has a collision
		{
			string* collarray = new string[big]; //array storing non-duplicate keys that generate the same hash key
			for (HashList<HashNode> :: iterator it = buckets[i].begin(); it != buckets[i].end(); ++it) //loops through the list at buckets[i]
			{
				for (int k = 0; k < big; k++) //loops through the collarray
				{
					if (collarray[k] == it.operator*().key) 
					{
						inarray = true; //if a key in the buckets[i] exists in the collarray, we set inarray to true
					}
				}
				if (inarray == false)
				{
					collarray[index] = it.operator*().key; //only add a key to the collarray if inarray is false
					index++; //increment the index
					big++; //increase the size of the array
				}
			}
			collisions += (big-1); // calculate the collisions before the collarray is reset and store it
		}
	}

	cout<<"Total number of collisions: "<<collisions<<endl;

	return collisions;
}

int FlightHASHTABLE::exportCSV(string path)
{
	int exported = 0;
	ofstream outflightdata;
	outflightdata.open(path, ofstream::out | ofstream::app);
	for (int i = 0; i < capacity; i++)
	{
		for (HashList<HashNode> :: iterator it = buckets[i].begin(); it != buckets[i].end(); ++it)
		{
			outflightdata << it.operator*().value.companyName<<','<<it.operator*().value.flightNumber<<','<<it.operator*().value.country_of_origin<<','<<it.operator*().value.country_of_destination<<','<<it.operator*().value.stopOver<<','<<it.operator*().value.price<<','<<it.operator*().value.time_of_departure<<','<<it.operator*().value.time_of_arrival<<','<<it.operator*().value.date<<endl; //prints a flight ticket onto a csv file
			exported++;
		}
	}
	outflightdata.close();
	cout<<exported<<endl; //prints the total number of exported flight tickets
	return exported;
}

void FlightHASHTABLE::printASC(string companyName, int flightNumber)
{
	int i = 0;
	string key;
	key = companyName + to_string(flightNumber);
	long index = hash(key);
	string* sorting = new string[capacity];
	for (HashList<HashNode> :: iterator it = buckets[index].begin(); it != buckets[index].end(); ++it)
	{
		if (it.operator*().value.companyName == companyName && it.operator*().value.flightNumber == flightNumber)
		{
			sorting[i] = it.operator*().value.country_of_destination; //store each flight ticket with matching data in an array called sorting
		}
	}
	string small;
	int pos;
	//algorithm for sorting the array sorting (selection sort) 
	for (i = 0; i < sizeof(sorting)-1; i++)
	{
		small= sorting[i];
		pos = i;
 
		for(int j = i+1 ; j < sizeof(sorting); j++)
		{
 
		if (sorting[j] < small)
		{
		small = sorting[j];
		pos = j;
		}
		}
 
		if ( pos != i)
		{
		string temp = sorting[i];
		sorting[i] = sorting[pos];
		sorting[pos] = temp;
		}
	}
	int printed = 0;
	int sortindex = 0;
	while (printed != sizeof(sorting))
	{
		for (HashList<HashNode> :: iterator it = buckets[index].begin(); it != buckets[index].end(); ++it)
		{
			if (it.operator*().value.companyName == companyName && it.operator*().value.flightNumber == flightNumber && it.operator*().value.country_of_destination == sorting[sortindex]) //finds the flight ticket matching sorting[sortindex] then prints it
			{
				cout << it.operator*().value.companyName<<','<<it.operator*().value.flightNumber<<','<<it.operator*().value.country_of_origin<<','<<it.operator*().value.country_of_destination<<','<<it.operator*().value.stopOver<<','<<it.operator*().value.price<<','<<it.operator*().value.time_of_departure<<','<<it.operator*().value.time_of_arrival<<','<<it.operator*().value.date<<endl;
				printed++;
				sortindex++;
			}
		}
	}
}