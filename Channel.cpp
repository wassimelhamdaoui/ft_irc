#include "headers.hpp"
#include "Channel.hpp"

//constructors
Channel::Channel()
{
	this->_name = "";
	this->_pass = "";
	this->_mode = "";
	this->_topic = "";
	this->_limit = CHANMAX;
	this->_is_private = false;
	this->_inviteMode = false;
	this->_topicMode = false;
	this->_limitMode = false;
}

Channel::Channel(std::string name, std::string pass)
{
	this->_name = name;
	this->_pass = pass;
	this->_mode = "";
	this->_topic = "";
	this->_limit = CHANMAX;
	this->_inviteMode = false;
	this->_is_private = false;
	this->_topicMode = false;
	this->_limitMode = false;
}


Channel::~Channel()
{
}

//getters
std::string Channel::get_name() const
{
	return (this->_name);
}
std::string Channel::get_pass() const
{
	return (this->_pass);
}
std::string Channel::get_topic() const
{
	return (this->_topic);
}
std::string Channel::get_mode() const
{
	return (this->_mode);
}
int Channel::get_limit() const
{
	return this->_limit;
}
bool Channel::get_inviteMode() const
{
	return (this->_inviteMode);
}
bool		Channel::get_is_private() const
{
	return (this->_is_private);
}

bool Channel::get_topicMode() const
{
	return this->_topicMode;
}

bool Channel::get_limitMode() const
{
	return this->_limitMode;
}

std::string Channel::get_creation_time() const
{
	return	this->_creation_time;
}

std::vector<int> Channel::get_members() const
{
	return this->members;
}

std::vector<int> Channel::get_moderators() const
{
	return this->_moderators;
}

//setters
void Channel::set_name(std::string name)
{
	this->_name = name;
}
void Channel::set_creation_time(std::string time)
{
	this->_creation_time = time;
}
void Channel::set_pass(std::string pass)
{
	this->_pass = pass;
}
void Channel::set_topic(std::string topic)
{
	this->_topic = topic;
}
void Channel::set_mode(std::string mode)
{
	this->_mode = mode;
}
void Channel::set_limit(int limit)
{
	this->_limit = limit;
}
void Channel::set_inviteMode(bool _inviteMode)
{
	this->_inviteMode = _inviteMode;
}
void Channel::set_is_private(bool is_private)
{
	this->_is_private = is_private;
}

void Channel::set_topicMode(bool topicMode)
{
	this->_topicMode = topicMode;
}

void Channel::set_limitMode(bool limitMode)
{
	this->_limitMode = limitMode;
}

//methods
void Channel::add_member(int fd)
{
	this->members.push_back(fd);
}
void Channel::add_moderator(int fd)
{
	this->_moderators.push_back(fd);
}

void Channel::add_invited_list(std::string nick)
{
	this->_invited_list.push_back(nick);
}

bool Channel::is_invited(std::string nick)
{
	for (size_t i = 0; i < this->_invited_list.size(); i++)
	{
		if (this->_invited_list[i] == nick)
			return true;
	}
	return false;
}

// for part

bool Channel::channel_exist(std::map<std::string, Channel> &channels, std::string channel_name)
{
	std::map<std::string, Channel>::iterator it = channels.begin();
	std::map<std::string, Channel>::iterator ite = channels.end();
	for (; it != ite; it++)
	{
		if (it->first == channel_name)
			return true;
	}
	return false;
}

bool Channel::is_member(int fd)
{
	for (size_t i = 0; i < this->members.size(); i++)
	{
		if (this->members[i] == fd)
			return true;
	}
	return false;
}

bool Channel::is_moderator(int fd)
{
	for (size_t i = 0; i < this->_moderators.size(); i++)
	{
		if (this->_moderators[i] == fd)
			return true;
	}
	return false;
}

void Channel::remove_member(int fd)
{
	for (size_t i = 0; i < this->members.size(); i++)
	{
		if (this->members[i] == fd)
		{
			this->members.erase(this->members.begin() + i);
			return;
		}
	}
}

bool	Channel::is_empty() const
{
	if(this->get_name().empty())
		return true;
	return false;
	
}



// send message to all members of channel

void Channel::broadcast_message(std::string message, std::string nick, int fd)
{
	for (size_t i = 0; i < this->members.size(); i++)
	{
		if (this->members[i] != fd)
		{
			std::string msg = nick + ": " + message;
			send(this->members[i], msg.c_str(), msg.size(), 0);
		}
	}
}



