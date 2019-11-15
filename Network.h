#pragma once
#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <vector>

using namespace std;

class FriendRequest;
class User;
class Wall;

class Network
{
public:
	Network();
	~Network();

	void queueRequest(FriendRequest fr);
	void printQueue();
	void friendApproval(User*, User*, FriendRequest*, int global);
	void addUser(Network* sNetwork);
	bool isFriend(User*, User*);
	void storeWall(Wall*);
	vector<string> mutualFriends(User*, User*);
	void clearTemp();
	vector<User*> userList;

private:
	bool allowanceCheck = false;
	vector<string> tempMutuals;
	vector<FriendRequest> allRequests;
	int allowance;
	vector<Wall*> allWalls;
};

#endif
