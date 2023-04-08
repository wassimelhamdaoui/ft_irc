#include "headers.hpp"
#include "Channel.hpp"

//constructors
Channel::Channel()
{
	this->_name = "";
	this->_pass = "";
	this->_topic = "";
	this->_is_private = false;
	this->invite_only = false;
}

Channel::Channel(std::string name, std::string pass)
{
	this->_name = name;
	this->_pass = pass;
	this->_topic = "";
	this->invite_only = false;
	this->_is_private = false;
}

Channel::Channel(const Channel &copy)
{
	*this = copy;
}

Channel &Channel::operator=(const Channel &copy)
{
	this->_name = copy._name;
	this->_pass = copy._pass;
	this->_topic = copy._topic;
	this->invite_only = copy.invite_only;
	this->_is_private = copy._is_private;
	this->members = copy.members;
	this->_moderators = copy._moderators;
	this->_bans_list = copy._bans_list;
	this->_invited_list = copy._invited_list;
	return (*this);
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
bool 		Channel::get_invite_only() const
{
	return (this->invite_only);
}
bool		Channel::get_is_private() const
{
	return (this->_is_private);
}

std::vector<int> Channel::get_members() const
{
	return std::vector<int>();
}

//setters
void Channel::set_name(std::string name)
{
	this->_name = name;
}
void Channel::set_pass(std::string pass)
{
	this->_pass = pass;
}
void Channel::set_topic(std::string topic)
{
	this->_topic = topic;
}
void Channel::set_invite_only(bool invite_only)
{
	this->invite_only = invite_only;
}
void Channel::set_is_private(bool is_private)
{
	this->_is_private = is_private;
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

bool Channel::is_invited(std::string nick)
{
	for (size_t i = 0; i < this->_invited_list.size(); i++)
	{
		if (this->_invited_list[i] == nick)
			return true;
	}
	return false;
}
