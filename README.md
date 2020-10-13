# boostnetworking
Server/Client Networking Programs Using Boost Library

# Author: Cody Martin

## Server/Client Networking Programs

This program is to read and process three message types from a Client Program:

1) Identification Message
2) Password Message
3) Data Message(s)


## Client Program Description

The Client program uses the Boost.Asio 1.69.0 Library for C++ to set up a
connection to a port that the Server program listens to on localhost.

The Client program uses stdin via the terminal window to retrieve the
three message types from the user. 

We set up an infinite loop that allows the user to send multiple messages in 
a synchronous order to the Server program. The user must enter "exit" to stop
the loop and signal the end of the data messages.

The program then sends all data messages via a socket connection
and a data buffer to the Server Program.


## Server Program Description

The Server program uses the same Boost.Asio library to set up a 
socket connection that listens on a specific port that the Client will send
data through.

The program listens on the specific port via an Asio acceptor variable that
uses the socket created by the Server Program.

We retrieve username ID and password and immediately write both
to terminal and file. We set an infinite loop to retrieve data messages
sent by the Client until the Server program retrieves "exit" string.

Raw string data message is then written to the terminal output window and
to the file in which holds the username ID and password. 

String data message is then sent to another function to parse data which
are written to a separate output file as well terminal output. Purpose of
the parser is to take a string object, then parse all valid numbers into
integers.


## Usage of Client/Server Programs

0) Programs are meant to be on Linux OS
1) Server program should be run first to listen for client connection.
2) Client program will be ran.
3) User will input Identification Message
4) User will input Password Message
5) User will input their Data Message(s) to be parsed.
6) At this point, user enters "exit" to stop the program when user is
   finished entering their Data Message(s)
