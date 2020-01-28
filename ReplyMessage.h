#pragma once
#include "Message.h"

class ReplyMessage :
	public Message
{
public:
	ReplyMessage();
	ReplyMessage(User*, Network*);
	~ReplyMessage();
	User* creator;
private:
	string post;
	
	Network* socialNetwork;
};

