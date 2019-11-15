#include "stdafx.h"
#include "Message.h"
#include "Network.h"
#include "User.h"
#include "FriendRequest.h"
#include "Wall.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <time.h>
#include <fstream>


using namespace std;

Message::Message()
{
}

Message::~Message()
{
}

Message::Message(User* Creator, Network* socialNetwork)
{
	this->creator = Creator;
	this->socialNetwork = socialNetwork;

	time_t now = time(0);
	// convert now to string form
	timestamp = ctime(&now);
	cout << "Timestamp is" << timestamp << endl;
	int size = strlen(timestamp);
	s.assign(timestamp, size);

	
	this->toString();
}

string Message::getPost()
{
	return post;
}

void Message::setLikes()
{
	likes++;
}

int Message::getLikes()
{
	return likes;
}

void Message::toString()
{
	cout << "Please enter your message: " << '\n' << '\n';
	cin.ignore(0);
	getline(cin,post);
	cout << "Your message is: " << post << endl;
}

string Message::getTimestamp()
{
	return s;
}

string Message::getCreator()
{
	return creator->getName();
}
// Mporw na valw mia static metavliti wste na tin allazw kata +1 ekxwrwntas ti se kapoia alli metavliti counter gia na dw poio minima ftiaxtike prwto?