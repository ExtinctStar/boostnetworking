/***************************************************
/ Synchronous Server Program
/ @author Cody Martin
/ Using Boost 1.69.0 C++ Library.
/ Server processes and outputs all data from Client
/**************************************************/

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

/***************************************************************************
/ Reads Client's messages through streambuf and socket until newline char
/ Typecasts data to character string and returns data
/ @param socket: Provides reference to interface communication with Client
/**************************************************************************/
string getData(tcp::socket &socket)
{
    	boost::asio::streambuf dataBuffer;
   	read_until(socket, dataBuffer, "\n");
    	string data = buffer_cast<const char*>(dataBuffer.data());

    	return data;
}

/********************************************************************
/ Function template to write data of a generic type to a given file
/ @param fileName: output text file name
/ @param data: generic data message to be written to file
/*******************************************************************/
template <class T>
void writeFile(char fileName[], T data)
{
	ofstream ofFile;

	//fstream::app activates append mode on file
	ofFile.open(fileName, fstream::app);
	if(ofFile.is_open())
	{
		ofFile << data << endl;
	}
	else cout << "Failed to open file";
	ofFile.close();
}

/***********************************************************
/ Checks to see if file exists, then deletes existing file
/ @param fileName: output text file name
/**********************************************************/
void deleteFile(char fileName[])
{
	ifstream iFile(fileName);
	if(iFile)
	{
		remove(fileName);
	}
}

/******************************************************************
/ Basic parser that extracts the numbers of a data message string
/ and parses them from a string to an integer.
/ Outputs parsed data to terminal and a text file.
/ @param fileName: output text file name
/ @param rawData: string data to be parsed into integer
/*****************************************************************/
void parseToFile(char fileName[], string rawData)
{
    	int parsedData;
	ofstream ofFile;

    	istringstream issData(rawData);
   	string singleObject;

	//uses istringstream and getline to input into singleObject
	//delimited by a space
	cout << "Parsed Data (string -> int):\n";
    	while(getline(issData, singleObject, ' '))
    	{
        	try
        	{
            		parsedData = stoi(singleObject, nullptr, 10);
            		cout << parsedData << endl;

			writeFile(fileName, parsedData);
        	}
        	catch(...)
        	{
            		cout << "Invalid input: " << singleObject << endl;
        	}
    	}
}

/*
/ Main program that sets up socket connection for Server
/ and receives data from Client to be processed
/ Desc:	Sets up io_service to use Boost functions
/	Sets up acceptor to listen for a connection from Client on port 1234
/	Sets up socket connection for server
/	Server receives values from Client for id, data, and password
/	Terminal output is carried about by terminalOutput variable
/*/
int main()
{
    	io_service io_service;
    	tcp::acceptor serverAcceptor( io_service, tcp::endpoint(tcp::v4(), 1234));
    	tcp::socket serverSocket(io_service);

    	serverAcceptor.accept(serverSocket);

    	string terminalOut, id, data, password;

	//File needs to be deleted at the beginning of each run of the program
	//to delete data from previous program run.
	char outFileName[] = "userMessages.txt";
	deleteFile(outFileName);

	//For each string variable that is read from Client, there is a newline
	//character that needs to be removed before processing data.
    	id = getData(serverSocket);
	id.pop_back();				//deletes "\n" from data
    	terminalOut = "ID Message:\n" + id;
    	cout << terminalOut << endl;
	writeFile(outFileName, id);

	password = getData(serverSocket);
	password.pop_back();
	terminalOut = "Password Message:\n" + password;
	cout << terminalOut << endl;
	writeFile(outFileName, password);

	//Previous iteration of file should be deleted before processing
	char parsedFile[] = "parsedData.txt";
	deleteFile(parsedFile);

	//Infinite loop to read data messages from Client and parses data
	//"exit" is used to leave the loop
	while(true)
	{
		data = getData(serverSocket);
		data.pop_back();
		terminalOut = "Data Message:\n" + data;
		cout << terminalOut << endl;

		if(data == "exit")
			break;
		else
		{
			writeFile(outFileName, data);
			parseToFile(parsedFile, data);
		}
	}

    	return 0;
}
