#pragma once
#ifndef WALL_H
#define WALL_H

#include <string>
#include <vector>

class Network;
class User;
class Message;

using namespace std;

class Wall
{
public:
	Wall();
	Wall(User*, Network*);
	~Wall();
	void storePost(Message*);
	void printWall();
	bool canPost(User*);
	vector<Message*> allPosts;

private:
	Network* sNetwork;
	User* iUser;
	
};

#endif
