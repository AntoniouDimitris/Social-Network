#pragma once
#ifndef FRIENDREQUEST_H
#define FRIENDREQUEST_H

#include <string>
#include <vector>

class User;
class Network;

using namespace std;

class FriendRequest
{
public:
	FriendRequest();
	FriendRequest(User*, User*);
	~FriendRequest();

	void changeStatus(int);
	int getStatus();
	string getFromUser();
	string getToUser();
	User* getSender();
	User* getRecipient();

private:
	char* dt;
	int status;
	string fromUser;
	string toUser;
	User* sender;
	User* recipient;
};

#endif


