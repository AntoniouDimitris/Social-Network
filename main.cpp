#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <time.h>
#include <chrono>
#include <thread>
#include <limits>
#include "Network.h"
#include "FriendRequest.h"
#include "User.h"
#include "Message.h"
#include "Wall.h"
#include "Menu.h"
#include "Global.h"

using namespace std;


int main()
{
	int firstAction;
	int secondAction;
	int thirdAction;
	string yourname;
	bool exit = false;
	bool valid_input;
	bool logout;
	bool firstLoop = false;
	bool secondLoop = true;

	Network *sNetwork = new Network();

	cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "------------re----------" << endl;
	cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "*WELCOME TO HANDSHAKE*" << endl;
	cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "----------------------" << endl << endl;
	cout << '\t' << '\t' << "--Please note that only the first word will be taken into consideration for each entry--" << endl << endl;

	try {
		while (firstCheck != "done")
		{
			cout << "REGISTER USER'S NAME AND EMAIL. " << endl << "Type \"done\" if registering process is over" << endl << endl;
			if (firstCheck == "done")
			{
				break;
			}
			sNetwork->addUser(sNetwork);
		}
		for (int i = 0; i < sNetwork->userList.size(); ++i)
		{
			cout << sNetwork->userList[i]->getName() << endl;
		}
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}

	do 
	{
		do 
		{
			logout = false;
			valid_input = false;
			cout << "That input is invalid!" << endl << endl;

			do {
				cout << "Select an action:" << endl << "1 - Log in" << endl << "2 - Exit" << endl;
				cin >> firstAction;

				if (!(valid_input = cin.good())) {
					cout << "That input is invalid!" << endl << endl;
					cin.clear();
					cin.ignore(300, '\n');
				}

			} while (!valid_input);

			if (firstAction == 1 || firstAction == 2) break;
			
		} while (true);
		
		switch (firstAction)
		{
		case 1:
		{
			do
			{
				cout << "Please enter your username: " << endl;
				cin >> yourname;

				for (unsigned int i = 0; i < sNetwork->userList.size(); ++i)
				{
					if (yourname == sNetwork->userList[i]->getName())
					{
						firstLoop = true;
					}
				}
			} while (firstLoop == false);

			Menu *userMenu = new Menu();

			for (unsigned int i = 0; i < sNetwork->userList.size(); ++i)
			{
				if (yourname == sNetwork->userList[i]->getName())
				{
					userMenu->setNetwork(sNetwork);
					userMenu->setUser(sNetwork->userList[i]);
				}
			}


			while (secondLoop == true)
			{
				cout << "Select your action:" << endl << "1 - Browse your wall" << endl << "2 - Browse your friends' wall" << endl << "3 - Send a friend request to available users" << endl << "4 - Manage your friend requests" << endl << "5 - See your friend list" << endl << "6 - Log out" << endl << "7 - Exit" << endl << endl;
				cin >> secondAction;
				cout << endl;

				switch (secondAction)
				{
				case 1:
					userMenu->seeMyWall();
					break;
				case 2:
					userMenu->seeFriendsWall();
					cout << endl << "1 - Post on " << userMenu->getTempFriend() << "'s wall" << endl;
					cin >> thirdAction;
					switch (thirdAction)
					{
					case 1:
						userMenu->postOnFriendsWall();
						break;
					}
					break;
				case 3:
					userMenu->sendFriendRequest();
					break;
				case 4:
					userMenu->handleRequests();
					break;
				case 5:
					userMenu->getUser()->getFriendList();
					break;
				case 6:
					logout = true;
					break;
				case 7:
					secondLoop = false;
					exit = true;
					break;
				}

				if (logout)
				{
					break;
				}
			}
		}
		break;

		case 2:
			exit = true;
			break;
		}
		
		if (exit == true)
		{
			cout << '\t' << '\t' << '\t' << '\t' << '\t' << "  " << "Till our next handshake!" << endl;
			for (int seconds = 3; seconds >= 0; seconds--)
			{
				cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "Exiting in " << seconds << '\r';

				this_thread::sleep_for(chrono::milliseconds(860));
			}
			return 0;
		}

	} while (true);

	cin.ignore();
	sNetwork->userList[2]->wallPost(sNetwork->userList[0]);
	sNetwork->userList[1]->wallPost(sNetwork->userList[0]);
	sNetwork->userList[3]->wallPost(sNetwork->userList[0]);

	sNetwork->userList[3]->likePost(sNetwork->userList[0]->myWall->allPosts[1]);

	sNetwork->userList[0]->printWall();
}