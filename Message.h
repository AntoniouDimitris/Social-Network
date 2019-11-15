#pragma once
#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>

using namespace std;

class Network;
class User;
class FriendRequest;
class Wall;

class Message
{
public:
	Message();
	Message(User*, Network*);
	~Message();

	string getPost();
	void setLikes();
	int getLikes();
	void toString();
	string getTimestamp();
	string getCreator();
	
private:
	char* timestamp;
	string s;
	string post;
	User* creator;
	Network* socialNetwork;
	int likes = 0;
};

#endif