#pragma once
#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

using namespace std;

class User;
class Network;
class FriendRequest;
class Wall;
class Message;

class Menu
{
public:
	Menu();
	Menu(Network*, User*);
	~Menu();
	void setNetwork(Network*);
	void setUser(User*);
	string getTempFriend();
	User* getUser();
	void seeMyWall();
	int seeFriendsWall();
	void postOnFriendsWall();
	void sendFriendRequest(int);
	void sendFriendRequest();
	void handleRequests();
	void likeMessage();
	void replyTo();

private:
	bool invalid;
	int befriendChoice;
	int chooseFW;
	int numberOfPost;
	User* tempFriend;
	vector<User*> tempUsers;
	bool match;
	bool boundCheck = false;
	User* curUser;
	Network* sNetwork;
};

#endif
