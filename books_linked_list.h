#pragma once
#include <iostream>
#include <queue>
#include <string>
#include <cstdlib>

using namespace std;

class books {
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

	books();
	int idcount = 0;
	void Insert(string book_title, string author, int id);
	void DeleteNode(int id);
	void printList();
	void search(string &book_title, string &author, int &id);
	void searchtitle(string &book_title);
	void Add(string book_title, string author);
};


// constructor sets head, current and temp to NULL
books::books()
{
	head = NULL;
	current = NULL;
	temp = NULL;
}

// inserts a brand new book
void books::Add(string book_title, string author)
{
	nodePtr n = new node;
	n->next = NULL;
	n->book_title = book_title;
	n->author = author;
	idcount = idcount + 1;
	n->id = idcount;
	if (head == NULL || head->id > n->id) {
		n->next = head;
		head = n;
		// std::cout << n->book_title << " is added with ID " << n->id << "\n";
		return;
	}
	else {
		current = head;
		while (current->next != NULL && current->next->id < n->id)
			current = current->next;
		n->next = current->next;
		current->next = n;
		// std::cout << n->book_title << " is added with ID " << n->id << "\n";
	}
}

// adds book to list of books (used for adding existing book in library but loaned out to someone)
void books::Insert(string book_title, string author, int id)
{
	nodePtr n = new node;
	n->next = NULL;
	n->book_title = book_title;
	n->author = author;
	n->id = id;
	if (head == NULL || head->id > n->id) {
		n->next = head;
		head = n;
		return;
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

// deletes a node from the list of library books
void books::DeleteNode(int id)
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

// prints all the books in the library
void books::printList()
{
	current = head;
	while (current != NULL)
	{		
		std::cout << "\nBook ID: " << current->id << "\n";
		std::cout << "Book Title: " << current->book_title << "\n";
		std::cout << "Book Author: " << current->author << "\n\n";
		std::cout << "====================" << std::endl;

		current = current->next;
	}
}

// searches for the book based on book id and then 
void books::search(string &book_title, string &author, int &id)
{
	current = head;

	while (current != NULL && current->id < id)
	{
		current = current->next;
	}
	if (current == NULL || current->id > id)
	{
		std::cout << "That book you are looking for does not exist.\n";
		id = NULL;
	}
	else if (current->id == id) {
		
		book_title = current->book_title;
		author = current->author;
		id = current->id;
	}
}

// fetches the book title based on book (used in option 1 search book by title)
void books::searchtitle(string &book_title)
{
	current = head;
	while (current != NULL)
	{		
		if (current->book_title.compare(book_title) == 0) {
			std::cout << "\nBook ID: " << current->id << "\n";
			std::cout << "Book Title: " << current->book_title << "\n";
			std::cout << "Book Author: " << current->author << "\n\n";
		}
		current = current->next;
	}

	if (current == NULL) {
		std::cout << "That book you are looking for does not exist.\n";
	}
}