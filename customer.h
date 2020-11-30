#pragma once
#include <iostream>
#include <queue>
#include <string>
#include <random>
#include <cstdlib>

using namespace std;

class StringDynamicArray
{
public:
	StringDynamicArray()
	{
		currentSize = 0;
		maxSize = 10;
		dynamicArray = new string[maxSize];
	}

	int add(string x);
	bool remove(string x);
	void print();
	bool isEmpty();

private:
	string* dynamicArray;
	int currentSize;
	int maxSize;
};

bool StringDynamicArray::isEmpty()
{
	if (dynamicArray[0] == "")
		return true;
}

// function to add book to dynamic array
int StringDynamicArray::add(string title)
{
	if (currentSize == maxSize)
	{
		maxSize = maxSize * 2;
		string* tempArray = new string[maxSize];

		for (int i = 0; i < currentSize; i++)
		{
			tempArray[i] = dynamicArray[i];
		}

		tempArray[currentSize] = title;
		currentSize++;
		dynamicArray = tempArray;
	}
	else
	{
		dynamicArray[currentSize] = title;
		currentSize++;
	}
	return currentSize;
}

// function to remove book from dynamic array
bool StringDynamicArray::remove(string x)
{
	for (int i = 0; i < currentSize; i++)
	{
		if (dynamicArray[i] == x)
		{
			for (; i < currentSize - 1; i++)
			{
				// Assign the next element to current location.             
				dynamicArray[i] = dynamicArray[i + 1];
			}

			// Remove the last element as it has been moved to previous index.
			dynamicArray[currentSize - 1] = "";

			// push the index back by 1
			currentSize -= 1;
			
			return true;
		}
	}
	return false;
}

// prints all the books from the dynamic book array
void StringDynamicArray::print()
{
	for (int i = 0; i < currentSize; i++)
	{
		if (dynamicArray[i] == "")
		{
			break;
		}

		cout << dynamicArray[i] << endl;
	}
}

// user link list node
class user {

	typedef struct User {

		string user_name;
		int user_id;
		StringDynamicArray stringDynArray;
		User* next;

	} *userPtr;

	userPtr head, current;


public:

	// methods	
	void insert(string name);
	void removeUser(int id);
	void printUsers();
	bool searchUser(int searchID, string book_title);
	bool searchUserReturnBook(int searchID, string book_title);

	// books dynamic array
	void returnBook(string title);
	void addBorrowedBook(string title);
	void printAllBooks();

	user();
};

// returns the book (remove book title from dynamic string array)
void user::returnBook(string title)
{
	current->stringDynArray.remove(title);
}

// adds book to list of borrowed books (adds the book title to the dynamic string array)
void user::addBorrowedBook(string title)
{
	current->stringDynArray.add(title);
}

// prints all borrowed books 
void user::printAllBooks()
{
	current->stringDynArray.print();
}

// constructor sets head and current to null
user::user()
{
	head = NULL;
	current = NULL;
}

// searchUser() looks for user based on ID and loans the book to them (add the book title to their String array)
bool user::searchUser(int searchID, string book_title)
{
	current = head;
	while (current != NULL && current->user_id != searchID)
	{
		current = current->next;
	}

	if (current == NULL) {
		cout << "Sorry that user does not exist.\n";
		return false;
	}
	else {
		current->stringDynArray.add(book_title);
		cout << "Book successfully loaned to: " << current->user_name << endl;
		return true;
	}
}

// searches for the user based on id and removes the book title from the dynamic string array
bool user::searchUserReturnBook(int searchID, string book_title)
{
	current = head;
	while (current != NULL && current->user_id != searchID)
	{
		current = current->next;
	}

	if (current == NULL) {
		cout << "Sorry that user does not exist.\n";
		return false;
	}
	else {
		current->stringDynArray.remove(book_title);
		cout << "Book " << book_title << " successfully returned by: " << current->user_name << endl;
		return true;
	}
}

// creates a new user
void user::insert(string name)
{
	userPtr new_node = new User();
	new_node->user_name = name;
	new_node->user_id = rand() % 100000 + 1; // generates a random number from 1 to 100,000
	new_node->next = NULL;

	if (head != NULL)
	{
		current = head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
	else {
		head = new_node;
	}
}

// prints all the users
void user::printUsers()
{
	current = head;
	while (current != NULL)
	{
		cout << current->user_name << "\n" << "id: " << current->user_id << endl;
		cout << "Borrowed Books: " << endl;
		current->stringDynArray.print();
		current = current->next;

		cout << "====================\n";
	}

	if (head == NULL) // if no one is in database execute
		cout << "The user database is empty.\n";
}

// removes the user
void user::removeUser(int id)
{
	userPtr delPtr = NULL, temp = NULL;
	current = temp = head;
	
	// iterates through the user link list
	while (current != NULL && current->user_id != id)
	{
		temp = current;
		current = current->next;
	}

	// executes if at the end of the list
	if (current == NULL)
	{
		cout << "That user does not exist.\n";
		delete delPtr;
	} 
	
	if(current->stringDynArray.isEmpty()) {
		delPtr = current; // delPtr is pointing to current node
		current = current->next; // current is set to next node
		temp->next = current; // temp's next node is new current

		if (delPtr == head) // if delPtr is head set head to next node
		{
			head = head->next;
			temp = NULL;
		}

		cout << "user " << id << " has been removed from database.\n";
		delete delPtr;
	}
	else {
		std::cout << "The user has pending books to return.\n";
		delete delPtr;
	}
}