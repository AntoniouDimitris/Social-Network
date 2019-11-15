#pragma once
#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <vector>

class FriendRequest;
class Network;
class Message;
class Wall;

using namespace std;

class User
{
public:
	User(Network*);
	User();
	~User();

	
	void sendRequest(User*);
	void receiveRequest(FriendRequest);
	void pR();
	void handleRequest(int, FriendRequest *);
	void printRequestStatus();
	void setName(string);
	void setEmail(string);
	string getName();
	string getEmail();
	void getFriendList();
	void likePost(Message* msg);

	vector<string> friendList;
	Network *socialNetwork;
	vector<FriendRequest> incRequests;
	void getLikedPosts();
	void wallPost(User*);
	void printWall();
	Wall* myWall;
	
private:
	bool nameCheck;
	bool nameTaken = false ;
	string name;
	string email;	
	vector <Message*> likedPosts;
	
	
};

#endif