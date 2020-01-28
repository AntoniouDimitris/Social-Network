#include "stdafx.h"
#include "Message.h"
#include "Network.h"
#include "User.h"
#include "FriendRequest.h"
#include "Wall.h"
#include "ReplyMessage.h"
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
	toString();
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
	getline(cin,post);
}

string Message::getTimestamp()
{
	return s;
}

string Message::getCreator()
{
	return creator->getName();
}

void Message::storeReply(ReplyMessage* reply)
{
	replies.push_back(reply);
}

void Message::printReplies()
{
	for (unsigned int i = 0; i < replies.size(); ++i)
	{
		cout << '\t' << '\t' << '\t' << "-" << replies[i]->getPost() << '\t' << '\t' << "From: " << replies[i]->creator->getName() << " at " << replies[i]->getTimestamp() << endl;
	}
}
