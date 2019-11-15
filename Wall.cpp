#include "stdafx.h"
#include "Wall.h"
#include "Network.h"
#include "User.h"
#include "Message.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Wall::Wall()
{
}

Wall::Wall(User* iUser, Network* sNetwork)
{
	this->iUser = iUser;
	this->sNetwork = sNetwork;
}

Wall::~Wall()
{
}

void Wall::storePost(Message* post)
{
	allPosts.push_back(post);
}

void Wall::printWall()
{
	for (unsigned int i = 0; i < allPosts.size(); ++i)
	{
		cout << allPosts[i]->getPost() << '\t' << "From: " << allPosts[i]->getCreator() << " at " << allPosts[i]->getTimestamp() << " -"  << allPosts[i]->getLikes() << "- " << endl;
		//cout << allPosts[i]->getLikes() << endl;
	}
}

bool Wall::canPost(User* User2)
{
	if (sNetwork->isFriend(iUser, User2))
	{
		return true;
	}
	else if (iUser == User2)
	{
		return true;
	}
	else
	{
		return false;
	}
}