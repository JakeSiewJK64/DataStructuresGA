#pragma once
#include <iostream>
#include <queue>
#include <string>
#include <cstdlib>

using namespace std;

class borrowed_books {
private:

	typedef struct node {
		int id;
		string book_title, author;
		node* next;
	}*nodePtr;

	nodePtr head;
	nodePtr current;
	nodePtr temp;

public:

	borrowed_books();

	void Insert(string book_title, string author, int id);
	void DeleteNode(int id);
	void search(string &book_title, string &author, int &id);
	string getBookTitle(int &id);
	string getBookAuthor(int &id);
};

// constructor initialize head, current and temp to NULL
borrowed_books::borrowed_books()
{
	head = NULL;
	current = NULL;
	temp = NULL;
}

// inserts a book to list of loaned books
void borrowed_books::Insert(string book_title, string author, int id)
{
	nodePtr n = new node;
	n->next = NULL;
	n->book_title = book_title;
	n->author = author;
	n->id = id;

	if (head == NULL || head->id > n->id) {
		n->next = head;
		head = n;
	}
	else if (head->id == n->id) {
		std::cout << id << " already exists\n";
	}
	else {
		current = head;

		while (current->next != NULL && current->next->id < n->id)
			current = current->next;
		if (current->next != NULL && current->next->id == n->id) {
		std:cout << id << " already exists\n";
			return;
		}
		n->next = current->next;
		current->next = n;
	}
}

// removes a book from the list of loaned books (returned the book)
void borrowed_books::DeleteNode(int id)
{
	nodePtr delPtr = NULL;
	temp = head;
	current = head;
	while (current != NULL && current->id < id)
	{
		temp = current;
		current = current->next;
	}

	if (current == NULL || current->id > id) {
		std::cout << "ID " << id << " was not in the list\n";
		delete delPtr;
	}
	else {
		delPtr = current;
		current = current->next;
		temp->next = current;

		if (delPtr == head) {
			head = head->next;
			temp = NULL;
		}

		delete delPtr;
		std::cout << "the value " << id << " has been removed.\n";
	}
}

// gets the book title based on the book ID
string borrowed_books::getBookTitle(int &searchid)
{
	current = head;

	while (current != NULL && current->id != searchid)
	{		
		current = current->next;
	}
	
	if (current == NULL)
	{
		std::cout << "Sorry, the book has not been loaned.\n" << std::endl;
		return " ";
	}

	if (current->id == searchid) {

		return current->book_title;
	}	
}

// 
void borrowed_books::search(string &book_title, string &author, int &id)
{
	current = head;

	while (current != NULL && current->id < id)
	{
		current = current->next;
	}
	if (current == NULL || current->id > id)
	{
		std::cout << "That book has not been loaned.\n";
		id = NULL;
	}
	else {
		book_title = current->book_title;
		author = current->author;
		id = current->id;
	}
}

// gets the book author based on book id
string borrowed_books::getBookAuthor(int &searchid)
{
	current = head;

	while (current != NULL)
	{
		if (current->id == searchid) {

			return current->author;
		}
		else current = current->next;
	}

	if (current == NULL)
	{
		std::cout << "Sorry, the book has not been loaned.\n" << std::endl;
	}
}