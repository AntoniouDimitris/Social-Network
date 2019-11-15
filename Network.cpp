#include "stdafx.h"
#include "Network.h"
#include "User.h"
#include "Wall.h"
#include "FriendRequest.h"
#include <iostream>
#include <string>
#include <vector>
#include "Global.h"

using namespace std;

Network::Network()
{
}


Network::~Network()
{
}

void Network::queueRequest(FriendRequest fr)
{
	allRequests.push_back(fr);
}


void Network::friendApproval(User* User1, User* User2, FriendRequest* rf, int global)
{
	
	for (unsigned int i = 0; i < User1->friendList.size(); ++i)
	{
		if (User1->friendList[i] == rf->getFromUser())
		{
			cout << "User already a friend" << endl;
			return;
		}
	}

	do
	{
		cout << "Enter \"1\" to accept or \"2\" to decline:  ";
		cin >> allowance;
		cout << endl;
		
		if (allowance != 1 && allowance != 2)
		{
			cout << "Number given not acceptable, try again! ";
			continue;
		}
		allowanceCheck = true;
	} while (allowanceCheck == false);

	User1->handleRequest(allowance, rf);

	if (rf->getStatus() == 1)
	{
		User2->friendList.push_back(rf->getToUser());
		User1->friendList.push_back(rf->getFromUser());
		rf->~FriendRequest();
		User1->incRequests.erase(User1->incRequests.begin() + global);
		
		for (unsigned int i = 0; i < User2->incRequests.size(); ++i)
		{
			if (User1->getName() == User2->incRequests[i].getFromUser())
			{
				User2->incRequests.erase(User2->incRequests.begin() + i);
			}
		}
	}

	else if (rf->getStatus() == 2)
	{
		rf->~FriendRequest();
		User1->incRequests.erase(User1->incRequests.begin() + global);
	}
}


void Network::printQueue()
{
	for (unsigned int i = 0; i < allRequests.size(); ++i)
	{
		cout << allRequests[i].getFromUser() << '\t' << allRequests[i].getToUser() << endl;
	}
}

void Network::addUser(Network *sNetwork)
{
	User* aUser = new User(sNetwork);
	userList.push_back(aUser);
}

bool Network::isFriend(User *User1, User *User2)
{
	for (int i = 0; i < User1->friendList.size(); ++i)
	{
		if (User2->getName() == User1->friendList[i])
		{
			return true;
		}
	}
	return false;
}

void Network::storeWall(Wall* aWall)
{
	allWalls.push_back(aWall);
}

vector<string> Network::mutualFriends(User* User1, User* User2)
{
	for (unsigned int i = 0; i < User1->friendList.size(); ++i)
	{
		for (unsigned int k = 0; k < User2->friendList.size(); ++k)
		{
			if (User1->friendList[i] == User2->friendList[k])
			{
				tempMutuals.push_back(User1->friendList[i]);
			}
		}
	}
	return tempMutuals; //meta to return sti me8odo pou tin kalei, prepei na ginei call tis clearTemp
}

void Network::clearTemp()
{
	tempMutuals.clear();
}