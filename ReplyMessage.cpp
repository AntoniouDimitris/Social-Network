#include "stdafx.h"
#include "ReplyMessage.h"
#include <ctime>
#include <time.h>
#include <iostream>


ReplyMessage::ReplyMessage()
{
}

ReplyMessage::ReplyMessage(User* Creator, Network* socialNetwork)
{
	this->creator = Creator;
	this->socialNetwork = socialNetwork;

	time_t now = time(0);
	// convert now to string form
	timestamp = ctime(&now);
	int size = strlen(timestamp);
	s.assign(timestamp, size);
	cin.clear();
	cin.ignore(1000, '\n');
	toString();
}



ReplyMessage::~ReplyMessage()
{
}
