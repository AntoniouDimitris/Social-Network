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

Wall::Wall(User* iUser, Network* sNetwork)								//constructor pou dexete orismata ton xristi pou antistoixei to wall kai to Network object
{
	this->iUser = iUser;
	this->sNetwork = sNetwork;
}

Wall::~Wall()
{
}

void Wall::storePost(Message* post)										//apo8ikefsi enos Message object
{
	allPosts.push_back(post);
}

void Wall::printWall()
{
	cout << "No." << '\t' << "Post" << endl;
	cout << "---------------------------------------------------" << endl;

	for (unsigned int i = 0; i < allPosts.size(); ++i)
	{
		cout << "(" << i << ")" << '\t' << allPosts[i]->getPost() << '\t' << '\t' << '\t' << '\t' << '\t' << "From: " << allPosts[i]->getCreator() << " at " << allPosts[i]->getTimestamp() << "        -" << allPosts[i]->getLikes() << "- " << "  Likes" << endl << endl;
		allPosts[i]->printReplies();
		cout << "---------------------------------------------------" << endl;
	}
}

bool Wall::canPost(User* User2)											//elegxos epitrepsimotitas
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
