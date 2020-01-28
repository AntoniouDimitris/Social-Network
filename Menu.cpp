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

Menu::Menu(Network* sNetwork, User* curUser)					//constructor me orismata to object tis Network kai ton xristi pou einai loggarismenos
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

int Menu::seeFriendsWall()
{
	cout << "List of friends:" << endl << "----------------" << endl;

	for (unsigned int i = 0; i < curUser->friendList.size(); ++i)
	{
		cout << i << '\t' << curUser->friendList[i] << endl;
	}

	if (curUser->friendList.empty())
	{
		cout << "There are no friends to browse..." << '\t' << "Returning to previous menu in 3 seconds!" << endl << endl;

		for (int seconds = 3; seconds >= 0; seconds--)
		{
			cout << '\t' << '\t' << '\t' << '\t' << "*" << seconds << "*" << '\r';

			this_thread::sleep_for(chrono::milliseconds(860));
		}
		cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\r';
		return -1;
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
				if (curUser->friendList[i] == sNetwork->userList[k]->getName())			//Pernoume to friend pou epilex8ike, koitazoume oti ontws iparxei
				{
					tempFriend = sNetwork->userList[k];									//kai apo8ikevoume to user object afto stin tempFriend 
				}
			}
		}
	}
	tempFriend->printWall();															//tipwnoume to wall tou mesw me8odou tis klasis User
}

void Menu::postOnFriendsWall()
{
	if (tempFriend->myWall->canPost(curUser))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		curUser->wallPost(tempFriend);
	}
}

void Menu::sendFriendRequest(int rgn)													//me8odos apostolis aitimatwn apo to file
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

	cout << endl;
	curUser->sendRequest(tempUsers[rgn]);
	tempUsers.clear();
}

void Menu::sendFriendRequest()															//me8odos apostolis aitimatwn			
{
	for (unsigned int i = 0; i < sNetwork->userList.size(); ++i)						//psaxnontas se olo to userList
	{
		match = false;

		if (sNetwork->userList[i]->getName() == curUser->getName())						//apokleioume ton idio to xristi	
		{
			match = true;
		}

		for (unsigned int k = 0; k < curUser->friendList.size(); ++k)	
		{
			if (sNetwork->userList[i]->getName() == curUser->friendList[k])				//kai opoion user einai filos tou
			{
				match = true;
				break;
			}
		}
		if (match == false)
		{
			tempUsers.push_back(sNetwork->userList[i]);									//kai apo8ikevoume ta ipoloipa users sto tempUsers
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
		cout << i << '\t' << tempUsers[i]->getName() << endl;							//tipwnoume ti lista me tous users pou den einai filoi tou
	}

	cout << endl << "Choose the number of the user you wish to add: ";

	do
	{
		boundCheck = false;
		cin >> befriendChoice;

		if (befriendChoice >= tempUsers.size() || befriendChoice < 0)
		{
			cout << "Enter a valid number from 0 - " << tempUsers.size() - 1 << ": ";
			continue;
		}
		boundCheck = true;
	} while (boundCheck == false);

	cout << endl;
	curUser->sendRequest(tempUsers[befriendChoice]);									//stelnoume request ston user pou antistoixei ston ari8mo pou eisagame(befriendChoice)
	tempUsers.clear();																	//ka8arizoume to tempUsers gia epanaxrisimopioisi
}

void Menu::handleRequests()
{
	curUser->pR();																		//me8odos tis User pou emfanizei ta requests

	do
	{
		if (curUser->incRequests.empty())
		{
			cout << "You have no friend requests..." << '\t' << '\t' << "Returning to previous menu in 3 seconds!" << endl << endl;

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

		if (global >= curUser->incRequests.size() || global < 0)																//elegxos egkirotitas ari8mou
		{
			cout << "Enter a valid number from 0 - " << curUser->incRequests.size() - 1 << endl;
			continue;
		}
		boundCheck = true;
	} while (boundCheck == false);

	sNetwork->friendApproval(curUser, curUser->incRequests[global].getSender(), &curUser->incRequests[global], global);			//klisi tis friendApproval apo tin klasi Network
}

void Menu::likeMessage()
{
	if (tempFriend->myWall->allPosts.empty())												//return sto previous menu an einai adeio to epilegmeno wall
	{
		cout << "There are no posts on this wall yet..." << '\t' << "Returning to previous menu in 3 seconds!" << endl << endl;
		for (int seconds = 3; seconds >= 0; seconds--)
		{
			cout << '\t' << '\t' << '\t' << '\t' << '\t' << "*" << seconds << "*" << '\r';

			this_thread::sleep_for(chrono::milliseconds(860));
		}
		cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\r';
		cout << endl;
		return;
	}

	cin.clear();
	cin.ignore(1000, '\n');
	cout << "Choose the number of the message you wish to like.";
	cin >> numberOfPost;
	invalid = true;

	for (unsigned int i = 0; i < tempFriend->myWall->allPosts.size(); ++i)					//elegxos egkirotitas epilogis
	{
		if (numberOfPost == i)
		{
			curUser->likePost(tempFriend->myWall->allPosts[i]);								//klisi tis likePost apo tin User
			invalid = false;
		}
	}
	if (invalid == true)																	//return sto previous menu an dw8ei ari8mos ektos tou evrous
	{
		cout << endl << "Invalid input. Returning..." << endl;
		this_thread::sleep_for(chrono::milliseconds(1500));
	}
	cin.clear();
	cin.ignore(1000, '\n');
}

void Menu::replyTo()
{
	cin.clear();
	cin.ignore(1000, '\n');
	cout << "Choose the number of the message you wish to reply to.";
	cin >> numberOfPost;
	invalid = true;

	for (unsigned int i = 0; i < tempFriend->myWall->allPosts.size(); ++i)
	{
		if (numberOfPost == i)
		{
			curUser->reply(tempFriend, i);													//klisi tis reply apo User
			invalid = false;
		}
	}
	if (invalid == true)
	{
		cout << endl << "Invalid input. Returning..." << endl;
		this_thread::sleep_for(chrono::milliseconds(1500));
		cin.clear();
		cin.ignore(1000, '\n');
	}

}


Menu::~Menu()
{
}

