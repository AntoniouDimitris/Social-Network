#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <time.h>

#include "FriendRequest.h"
#include "User.h"
#include "Network.h"

using namespace std;

FriendRequest::FriendRequest()
{
}


FriendRequest::~FriendRequest()
{
}


FriendRequest::FriendRequest(User *User1, User *User2)
{
	this->sender = User1;
	this->recipient = User2;
	time_t now = time(0);
	// convert now to string form
	dt = ctime(&now);

	fromUser = sender->getName();
	toUser = recipient->getName();
	
	cout << "The local date and time is: " << dt << endl;

	status = 2;
}

void FriendRequest::changeStatus(int flag)  //set friend request to accepted(1) or rejected(2)
{
	if (flag == 1)
	{
		status = 1;
	}
	else if (flag == 2)
	{
		status = 2;
	}
}

int FriendRequest::getStatus()
{
	return status;
}

string FriendRequest::getFromUser()
{
	return fromUser;
}

string FriendRequest::getToUser()
{
	return toUser;
}

User* FriendRequest::getSender()
{
	return sender;
}

User* FriendRequest::getRecipient()
{
	return recipient;
}