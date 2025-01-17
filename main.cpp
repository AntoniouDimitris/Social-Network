#include "stdafx.h"
#include <iostream>
#include <fstream>
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
	int rgn;
	string yourname;
	bool exit = false;
	bool valid_input;
	bool logout;
	bool firstLoop;
	bool secondLoop = true;

	Network *sNetwork = new Network();

	cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "----------------------" << endl;
	cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "*WELCOME TO HANDSHAKE*" << endl;
	cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "----------------------" << endl << endl;
	cout << '\t' << '\t' << "--Please note that only the first word will be taken into consideration for each entry--" << endl << endl;

	if (std::ifstream in{ "filename.txt" })
	{
		string word;
		while (in >> word)
		{
			sNetwork->autoFill(sNetwork, word);									//autoregister me xristes apo to arxeio
		}
	}
	else
	{
		//couldn't open file
	}

	for (unsigned int i = 0; i < sNetwork->userList.size(); ++i)
	{
		{
			rgn = rand() % 10;
			sNetwork->userList[i]->sendRequest(sNetwork->userList[rgn]);		//aftomati apostoli random requests metaksi twn xristwn
		}
	}

	try {
		while (firstCheck != "done")
		{
			cout << "REGISTER USER'S NAME AND EMAIL. " << endl << "Type \"done\" if registering process is over" << endl << endl;
			if (firstCheck == "done")
			{
				break;
			}
			sNetwork->addUser(sNetwork);										//kataxwrisi xristwn wspou na do8ei i leksi "done" san Username
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
			cout << endl;

			do {
				cout << "Select an action:" << endl << "1 - Log in" << endl << "2 - Exit" << endl;
				cin >> firstAction;

				if (!(valid_input = cin.good()) || (firstAction != 1 && firstAction != 2))
				{
					cout << "That input is invalid!" << endl << endl;
					cin.clear();
					cin.ignore(1000, '\n');
				}

			} while (firstAction != 1 && firstAction != 2);

			break;

		} while (true);

		switch (firstAction)
		{
		case 1:
		{
			do
			{
				cin.clear();
				cin.ignore(1000, '\n');
				firstLoop = false;
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
					userMenu->setNetwork(sNetwork);									//Afou ginei login me iparxon username dimiourgoume to object userMenu
					userMenu->setUser(sNetwork->userList[i]);						//kai setaroume to xristi kai to Network tou
				}
			}


			while (secondLoop == true)
			{
				do															//ekkinisi arxikou menu
				{
					cout << '\t' << '\t' << '\t' << '\t' << "Username: " << userMenu->getUser()->getName() << '\t' << "   " << "Email: " << userMenu->getUser()->getEmail() << endl;
					cout << "Select your action:" << endl << "1 - Browse your wall" << endl << "2 - Browse your friends' wall" << endl << "3 - Send a friend request to available users" << endl << "4 - Manage your friend requests" << endl << "5 - See your friend list" << endl << "6 - Log out" << endl << "7 - Exit" << endl << endl;
					cin >> secondAction;
					cin.clear();
					cin.ignore(1000, '\n');
					cout << endl;
				} while (secondAction != 1 && secondAction != 2 && secondAction != 3 && secondAction != 4 && secondAction != 5 && secondAction != 6 && secondAction != 7);

				switch (secondAction)
				{
				case 1:
					userMenu->seeMyWall();
					break;
				case 2:
					if (userMenu->seeFriendsWall() == -1)
					{
						break;
					}
					else
					{
						do													//ekkinisi defterevontos menu
						{
							cin.clear();
							cin.ignore(1000, '\n');
							cout << endl << "Select your action" << endl << "1 - Post on " << userMenu->getTempFriend() << "'s wall" << endl << "2 - Reply to message" << endl << "3 - Like a post" << endl;
							cin >> thirdAction;
						} while (thirdAction != 1 && thirdAction != 2 && thirdAction != 3);
						switch (thirdAction)
						{
						case 1:
							userMenu->postOnFriendsWall();
							break;
						case 2:
							userMenu->replyTo();
							break;
						case 3:
							userMenu->likeMessage();
							break;
						}
						break;
					}
				case 3:
					userMenu->sendFriendRequest();
					break;
				case 4:
					userMenu->handleRequests();
					break;
				case 5:
					userMenu->getUser()->getFriendList();
					break;
				case 6:														//epistrofi sto Log in menu
					logout = true;
					break;
				case 7:														//eksodos apo to programma
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

}

