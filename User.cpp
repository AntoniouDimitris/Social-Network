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
#include "ReplyMessage.h"
#include <Global.h>


using namespace std;

User::User(Network* sNetwork, string rName)							//constructor gia users apo to arxeio
{
	this->socialNetwork = sNetwork;
	name = rName;
	email = rName + "@gmail.com";
	myWall = new Wall(this, sNetwork);
	socialNetwork->storeWall(myWall);
}

User::User(Network* sNetwork)										//constructor gia neo user
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
			cout << "Username already taken, try again! " << endl;
			this_thread::sleep_for(chrono::milliseconds(860));
			cout << "Give valid User's name:  ";
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
		cin.clear();
		cin.ignore(1000, '\n');
	} while (nameCheck == true);									//elegxoi gia tin egkirotita tou onomatos pou prospa8oume na kanoume register

	firstCheck = name;

	if (name == "done")
	{
		cout << endl;
		throw invalid_argument("\t \t \t \t \t    -User registering phase ended-");
	}

	cin.ignore(20000, '\n');
	cout << endl;
	cout << "Give User's email:  ";
	cin >> email;
	cin.ignore(20000, '\n');
	cout << endl;
	myWall = new Wall(this, sNetwork);								//dimiourgia tou wall tou xristi
	socialNetwork->storeWall(myWall);
}


User::~User()
{

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
	receiver->receiveRequest(rf);									//apo8ikefsi tou friendrequest sto stack tou paralipti
}

void User::receiveRequest(FriendRequest rf)
{
	incRequests.push_back(rf);
}

void User::pR()														//ektipwsi listas aitimatwn
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
		rf->changeStatus(1);										//allagi tis metavlitis status tou FriendRequest object se accepted(1).
	}
	else if (acc == 2)
	{
		rf->changeStatus(2);										//allagi tis metavlitis status tou FriendRequest object se declined(2).
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

void User::getFriendList()														//ektipwsi tou friendlist tou xristi
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
			cout << "User already liked this post!" << endl;
			return;
		}
	}
	msg->setLikes();															//afksisi twn Likes tou post kata 1
	likedPosts.push_back(msg);													//simeiwsi oti o sigkekrimenos xristis exei kanei like s'afto to post kai de mporei na ksanakanei
}

void User::getLikedPosts()
{
	for (int i = 0; i < likedPosts.size(); ++i)
	{
		cout << likedPosts[i]->getPost();
	}
}

void User::wallPost(User* receivingUser)										//me8odos gia post enos minimatos sto wall enos allou xristi
{
	Message* aMsg = new Message(this, socialNetwork);
	receivingUser->myWall->storePost(aMsg);
}

void User::reply(User* receivingUser, int postNumber)							//me8odos gia reply se ena post sto wall enos allou xristi
{
	ReplyMessage* rMsg = new ReplyMessage(this, socialNetwork);
	receivingUser->myWall->allPosts[postNumber]->storeReply(rMsg);
}

void User::printWall()
{
  	cout << "Printing " << this->getName() << "'s Wall: " << endl;
	myWall->printWall();
}
