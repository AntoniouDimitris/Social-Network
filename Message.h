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
class ReplyMessage;
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
	void storeReply(ReplyMessage*);
	void printReplies();

protected:
	char* timestamp;
	string s;

private:
	vector<ReplyMessage*> replies;
	string post;
	User* creator;
	Network* socialNetwork;
	int likes = 0;
};

#endif