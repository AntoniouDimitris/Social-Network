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
	
	void seeMyWall();
	void seeFriendsWall();
	void postOnFriendsWall();
	void sendFriendRequest();
	void setNetwork(Network*);
	void setUser(User*);
	string getTempFriend();
	User* getUser();
	void handleRequests();

private:
	int befriendChoice;
	int chooseFW;
	User* tempFriend;
	vector<User*> tempUsers;
	bool match;
	bool boundCheck = false;
	User* curUser;
	Network* sNetwork;
};

#endif
