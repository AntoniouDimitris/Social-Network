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

void Network::printQueue()
{
	for (unsigned int i = 0; i < allRequests.size(); ++i)
	{
		cout << allRequests[i].getFromUser() << '\t' << allRequests[i].getToUser() << endl;
	}
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

	do																						//loop wste na dw8ei katallilos ari8mos
	{
		cout << "Enter \"1\" to accept or \"2\" to decline:  ";
		cin >> allowance;
		cout << endl;

		if (allowance != 1 && allowance != 2)												//gia apodoxi i oxi enos aitimatos
		{
			cout << "Number given not acceptable, try again! ";
			continue;
		}
		allowanceCheck = true;
	} while (allowanceCheck == false);

	User1->handleRequest(allowance, rf);													//me8odos diaxeirisis tou aitimatos, pou anikei stin User, me orismata 1 i 2 kai to object tou aitimatos

	if (rf->getStatus() == 1)
	{
		User2->friendList.push_back(rf->getToUser());										//push to lipti an einai 1 sto friendlist tou apostolea
		User1->friendList.push_back(rf->getFromUser());										//push ton apostolea an einai 1 sto friendlist tou lipti
		rf->~FriendRequest();										
		User1->incRequests.erase(User1->incRequests.begin() + global);						//diagrafi twn antikeimenwn tipou FriendRequest

		for (unsigned int i = 0; i < User2->incRequests.size(); ++i)
		{
			if (User1->getName() == User2->incRequests[i].getFromUser())
			{
				User2->incRequests.erase(User2->incRequests.begin() + i);					//diagrafi twn antikeimenwn tipou FriendRequest
			}
		}
	}

	else if (rf->getStatus() == 2)															//an exei epilex8ei 2, apla diagrafei twn antikeimenwn FriendRequest
	{
		rf->~FriendRequest();
		User1->incRequests.erase(User1->incRequests.begin() + global);
	}
}

void Network::addUser(Network *sNetwork)													//pros8iki enos neou xristi
{
	User* aUser = new User(sNetwork);
	userList.push_back(aUser);
}

void Network::autoFill(Network *sNetwork, string rName)										//pros8iki xristwn apo to arxeio
{
	User* aUser = new User(sNetwork, rName);
	userList.push_back(aUser);
}

bool Network::isFriend(User *User1, User *User2)											//me8odos elegxou filias 2 xristwn
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

vector<string> Network::mutualFriends(User* User1, User* User2)								//me8odos pou epistrefei lista koinwn filwn 2 xristwn
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
	return tempMutuals;																		//meta to return sti me8odo pou tin kalei, prepei na ginei call tis clearTemp
}

void Network::clearTemp()
{
	tempMutuals.clear();
}
