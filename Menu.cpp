#include "stdafx.h"
#include "Menu.h"
#include "Network.h"
#include "User.h"
#include "FriendRequest.h"
#include "Wall.h"
#include "Message.h"
#include "Global.h"

#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h> 
#include <chrono>
#include <thread>
#include <iomanip> 

using namespace std;

Menu::Menu()
{
}

Menu::Menu(Network* sNetwork, User* curUser)
{
	this->curUser = curUser;
	this->sNetwork = sNetwork;
}

void Menu::setNetwork(Network* sNetwork)
{
	this->sNetwork = sNetwork;
}

void Menu::setUser(User* curUser)
{
	this->curUser = curUser;
}

string Menu::getTempFriend()
{
	return tempFriend->getName();
}

User* Menu::getUser()
{
	return curUser;
}

void Menu::seeMyWall()
{
	curUser->printWall();
}

void Menu::seeFriendsWall()
{
	cout << "List of friends:" << endl << "----------------" << endl;
	for (unsigned int i = 0; i < curUser->friendList.size(); ++i)
	{
		cout << i << '\t' << curUser->friendList[i] << endl;
	}
	cout << "----------------" << endl << "Choose one of your friends' wall to browse: ";

	cin >> chooseFW;
	cout << endl;

	for (unsigned int i = 0; i < curUser->friendList.size(); ++i)
	{
		if (chooseFW == i)
		{
			for (unsigned int k = 0; k < sNetwork->userList.size(); ++k)
			{
				if (curUser->friendList[i] == sNetwork->userList[k]->getName())
				{
					tempFriend = sNetwork->userList[k];
				}
			}
		}
	}
	tempFriend->printWall();
}

void Menu::postOnFriendsWall()
{
	if (tempFriend->myWall->canPost(curUser))
	{
		cin.ignore();
		curUser->wallPost(tempFriend);
	}
}

void Menu::sendFriendRequest()
{
	for (unsigned int i = 0; i < sNetwork->userList.size(); ++i)
	{
		match = false;
		
		if (sNetwork->userList[i]->getName() == curUser->getName())
		{
			match = true;
		}

		for (unsigned int k = 0; k < curUser->friendList.size(); ++k)
		{
			if (sNetwork->userList[i]->getName() == curUser->friendList[k])
			{
				match = true;
				break;
			}
		}
		if (match == false) 
		{
			tempUsers.push_back(sNetwork->userList[i]);
		}
	}

	if (tempUsers.empty())
	{
		cout << "There are no available users..." << '\t' << "Returning to previous menu in 3 seconds!" << endl << endl;

		for (int seconds = 3; seconds >= 0; seconds--)
		{
			cout << '\t' << '\t' << '\t' << '\t' << "*" << seconds << "*" << '\r';

			this_thread::sleep_for(chrono::milliseconds(860));
		}
		cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\r';
		cout << endl;
		return;
	}

	for (unsigned int i = 0; i < tempUsers.size(); ++i)
	{
		cout << i << '\t' << tempUsers[i]->getName() << endl;
	}

	cout << endl << "Choose the number of the user you wish to add: ";
	cin >> befriendChoice;
	cout << endl;
	curUser->sendRequest(tempUsers[befriendChoice]);
	tempUsers.clear();	
}

void Menu::handleRequests()
{
	curUser->pR();

	do
	{
		if (curUser->incRequests.empty())
		{
			cout << "You have no friend requests..." << '\t' << "Returning to previous menu in 3 seconds!" << endl << endl;
			
			for (int seconds = 3; seconds >= 0; seconds--)
			{
				cout << '\t' << '\t' << '\t' << '\t' << "*" << seconds << "*" << '\r';
				
				this_thread::sleep_for(chrono::milliseconds(860));
			}
			cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\r';
			cout << endl;
			return;
		}
		cout << "Enter matching friend request number to handle:  ";
		cin >> global;
		cout << endl;

		if (global >= curUser->incRequests.size() || global < 0)
		{
			cout << "Enter a valid number from 0 - " << curUser->incRequests.size() - 1 << endl;
			continue;
		}
		boundCheck = true;
	} while (boundCheck == false);

	sNetwork->friendApproval(curUser, curUser->incRequests[global].getSender(), &curUser->incRequests[global], global);
}


Menu::~Menu()
{
}

