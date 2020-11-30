// ConsoleApplication21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iostream>
#include <list>
#include <string>
#include "books_linked_list.h"
#include "book_issued.h"
#include "customer.h"

using namespace std;

int main()
{
	char choice;
	int id;
	int book_id;
	string temp_name;

	string search_book_title_2 = "", author = "";

	books book_listing;

	borrowed_books issued_books;

	user user_database;


	// starter books
	book_listing.Add("Harry Potter", "jk rowling");
	book_listing.Add("Lord of the Rings", "JRR");
	book_listing.Add("Great Gatsby", "F.Scott Fitzgerald");
	book_listing.Add("Tenki no ko", "Makoto Shinkai");
	book_listing.Add("Kimi No Nawa", "Makoto Shinkai");

	while (true)
	{
		std::cout << "<!-- Welcome to advanced library management systems --!> \n";
		std::cout << "[1] to search for a book\n" <<
			"[2] to borrow a book\n" <<
			"[3] to return a book\n" <<
			"[4] to add to book.\n" <<
			"[5] to display all books.\n" <<
			"[6] to add a user.\n" <<
			"[7] to remove a user.\n" <<
			"[8] to display all user.\n";

		std::cout << "Please enter a function: ";

		std::cin >> choice;
		std::cin.ignore();

		switch (choice)
		{
		case'1': // searching for a book

			cout << "====================\n";
			std::cout << "Please enter a book title to search for: ";
			std::getline(cin, search_book_title_2);
			book_listing.searchtitle(search_book_title_2);
			break;

		case '2': // borrowing a book

			cout << "====================\n";
			cout << "Please enter user id: ";
			cin >> id;

			// try catch block if string is entered for user id
			while (cin.fail()) {
				cout << "Please enter a valid user id: ";
				cin.clear();
				std::cin.ignore(256, '\n');
				cin >> id;
			}
			cin.ignore();

			std::cout << "Please enter the book ID to borrow: ";
			cin >> book_id;
			// try catch block for if string is entered for book id
			while (cin.fail()) {
				cout << "Please enter a valid book id: ";
				cin.clear();
				std::cin.ignore(256, '\n');
				cin >> book_id;
			}

			// searches for the book in the book link list based on book id
			// if book is found then set search_book_title_2 and author based on the book found in the book linked list
			book_listing.search(search_book_title_2, author, book_id);

			// only executes if id is NOT null
			if (book_id != NULL) {

				// searchUser() method returns a boolean value
				// if can find user only then remove the book and add to borrowed books
				if (user_database.searchUser(id, search_book_title_2)) {
					issued_books.Insert(search_book_title_2, author, book_id);
					book_listing.DeleteNode(book_id);
				}
			}
			break;

		case '3':// returning/ inserting a book

			cout << "====================\n";

			// entering user id
			cout << "Please enter user id: ";
			cin >> id;
			// try catch block if string is entered for user id
			while (cin.fail()) {
				cout << "Please enter a valid user id: ";
				cin.clear();
				std::cin.ignore(256, '\n');
				cin >> id;
			}
			cin.ignore();

			// entering book id
			std::cout << "Please enter the book ID to return: ";
			cin >> book_id;
			// try catch block for if string is entered for book id
			while (cin.fail()) {
				cout << "Please enter a valid book id: ";
				cin.clear();
				std::cin.ignore(256, '\n');
				cin >> book_id;
			}

			// this checks whether the book exist within the user's list of borrowed books otherwise return "this book has not been loaned"
			issued_books.search(search_book_title_2, author, book_id);

			// only executes if user got enter book id
			if (book_id != NULL) {
								
				
				if (user_database.searchUserReturnBook(id, issued_books.getBookTitle(book_id))) {
					
					// inserts a book into book listing
					book_listing.Insert(issued_books.getBookTitle(book_id), issued_books.getBookAuthor(book_id), book_id);
					
					// deletes a book from the list of borrowed books
					issued_books.DeleteNode(book_id);					
				}
			}			

			break;

		case '4': // adding a book

			cout << "====================\n";

			std::cout << "Please enter title for book: ";
			getline(cin, search_book_title_2);

			std::cout << "Please enter author: ";
			getline(cin, author);

			book_listing.Add(search_book_title_2, author);
			break;

		case '5': // display all books in library
			cout << "====================\n";
			book_listing.printList();
			break;

		case '6': // add users
			cout << "====================\n";
			cout << "Please enter user name: ";
			getline(cin, temp_name);
			user_database.insert(temp_name);
			break;

		case '7': // removes user

			cout << "====================\n";
			cout << "Please enter user id: ";
			cin >> id;
			while (cin.fail()) {
				cout << "Please enter a valid user id: ";
				cin.clear();
				std::cin.ignore(256, '\n');
				cin >> id;
			}
			user_database.removeUser(id);

			break;

		case '8': // prints all user

			cout << "====================\n";
			user_database.printUsers();
			break;

		default:
			cout << "====================\n";
			std::cout << "Sorry, that option does not exist.\n";
			break;
		}

		search_book_title_2 = "";
		author = "";
		book_id = NULL;
		id = NULL;
	}
}