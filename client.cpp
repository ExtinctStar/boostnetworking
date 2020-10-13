/******************************************************
/ Synchronous Client Program
/ @author Cody Martin
/ Using Boost 1.69.0 C++ Library.
/ Client must provide their Username ID and password,
/ as well as data to be parsed.
/*****************************************************/

#include <boost/asio.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

/*****************************************************************************
/ Writes Client's Message on socket to send to Server
/ @param socket: Provides reference to interface communication with Server
/ @param message: The message being sent through socket and buffer
/ Adds newline character to provide a delimiter for processing data
/****************************************************************************/
void writeData(tcp::socket &socket, const string &message)
{
	write(socket, buffer(message + "\n"));
}

/**********************************************************************************
/ Main program to set up socket network programming connection
/ Desc:	Sets up io_service to use Boost functions
/	Sets up socket for client to connect with Server on localhost on port 1234
/	User provides value for username, password, and data via terminal input
/*********************************************************************************/
int main()
{
	io_service io_service;
	ip::tcp::socket clientSocket(io_service);

	clientSocket.connect( tcp::endpoint(address::from_string("127.0.0.1"), 1234));

	string username, password, data;

	cout << "Please enter your Username: ";
	getline(cin, username);
	writeData(clientSocket, username);

	cout << "Please enter your Password: ";
	getline(cin, password);
	writeData(clientSocket, password);

	//Infinite loop to send multiple data messages to Server
	cout << "\n(Enter \"exit\" after you are finished entering the last line of Data)\n";
	while(true)
	{
		cout << "Enter sequence of numbers, each separated by a space, to be parsed\n";
		getline(cin, data);
		writeData(clientSocket, data);

		if(data == "exit")
			break;
	}

	return 0;
}

