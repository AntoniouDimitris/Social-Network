#include "stdafx.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "User.h"
#include "FriendRequest.h"
#include "Network.h"
#include "Message.h"
#include "Wall.h"
#include <Global.h>

using namespace std;

User::User()
{
}

User::User(Network* sNetwork)
{
	this->socialNetwork = sNetwork;
	do
	{
		switch (nameTaken)
		{
		case false:
			cout << "Give valid User's name:  ";
			break;
		case true:
			cout << "Username already taken, try again: ";
			break;
		}

		nameCheck = false;
		cin >> name;
		
		for (int i = 0; i < socialNetwork->userList.size(); ++i)
		{
			if (name == socialNetwork->userList[i]->getName())
			{
				nameCheck = true;
				nameTaken = true;
			}
		}
		if (nameCheck == false)
		{
			break;
		}
	} while (nameCheck == true);

	firstCheck = name;

	if (name == "done")
	{
		throw invalid_argument("name");
	}
	
	cin.ignore(20000, '\n');
	cout << endl;
	cout << "Give User's email:  ";
	cin >> email;
	cin.ignore(20000, '\n');
	cout << endl;
	myWall = new Wall(this, sNetwork);
	socialNetwork->storeWall(myWall);
}


User::~User()
{
	cout << "destructor";
}


void User::sendRequest(User *receiver)
{
	if (receiver->getName() == this->getName())
	{
		cout << "You cannot befriend yourself!";
		return;
	}
	for (unsigned int i = 0; i < receiver->incRequests.size(); ++i)
	{
		if (this->getName() == receiver->incRequests[i].getFromUser())
		{
			cout << "You've sent a friend request to that user already!" << endl << endl;
			this_thread::sleep_for(chrono::milliseconds(1200));
			return;
		}
	}
	FriendRequest rf(this, receiver);
	socialNetwork->queueRequest(rf);
	receiver->receiveRequest(rf);
}

void User::receiveRequest(FriendRequest rf)
{
	incRequests.push_back(rf);
}

void User::pR()
{
	cout << "Printing " << this->name << "'s Friend Request List: " << endl;
	cout << "No." << '\t' << "From" << '\t' << "To" << endl;
	cout << "---" << '\t' << "----" << '\t' << "--" << endl << endl;
	for (unsigned int i = 0; i < incRequests.size(); ++i)
	{
		cout << i << '\t' << incRequests[i].getFromUser() << '\t' << incRequests[i].getToUser() << endl;
	}

	cout << endl;
}

void User::handleRequest(int acc, FriendRequest *rf)
{
	if (acc == 1)
	{
		rf->changeStatus(1);		
	}
	else if (acc == 2)
	{
		rf->changeStatus(2);
	}
	else return;
}

void User::printRequestStatus()
{
	for (unsigned int i = 0; i < incRequests.size(); ++i)
	{
		cout << incRequests[i].getStatus() << '\t' << incRequests[i].getStatus() << endl;
	}
}

void User::setName(string name)
{
	this->name = name;
}

void User::setEmail(string email)
{
	this->email = email;
}

string User::getName()
{
	return name;
}

string User::getEmail()
{
	return email;
}

void User::getFriendList()
{
	cout << "Printing " << getName() << "'s " <<  "friend list:" << endl;

	for (int i = 0; i < friendList.size(); ++i)
	{
		cout << friendList[i] << endl;
	}

	cout << endl;
	this_thread::sleep_for(chrono::milliseconds(1200));
}

void User::likePost(Message *msg)
{
	for (int i = 0; i < likedPosts.size(); ++i)
	{
		if (msg == likedPosts[i])
		{
			cout << "User already liked this post!";
			return;
		}
	}
	msg->setLikes();
	likedPosts.push_back(msg);
}

void User::getLikedPosts()
{
	for (int i = 0; i < likedPosts.size(); ++i)
	{
		cout << likedPosts[i]->getPost();
	}
}

void User::wallPost(User* receivingUser)
{
	Message* aMsg = new Message(this, socialNetwork);
	receivingUser->myWall->storePost(aMsg);
}

void User::printWall()
{
  	cout << "Printing " << this->getName() << "'s Wall: " << endl;
	myWall->printWall();
}