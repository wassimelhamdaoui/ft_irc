#include "Channel.hpp"

Channel::Channel(std::string name, std::string pass)
{
    this->_name = name;
    this->_pass = pass;
}

Channel::Channel()
{
}

Channel::Channel( const Channel & src )
{
}

Channel & Channel::operator=( const Channel & rhs )
{
    if ( this != &rhs )
    {
        this->_name = rhs._name;
        this->_pass = rhs._pass;
        this->_topic = rhs._topic;
        this->_aut_key = rhs._aut_key;
        this->members = rhs.members;
        this->_bans_list = rhs._bans_list;
        this->cannels = rhs.cannels;
    }
    return (*this);
}

Channel::~Channel()
{
}


/**********  Channel methodes *********/

std::string Channel::get_name()
{
    return this->_name;
}

std::string Channel::get_pass()
{
    return this->_pass;
}

std::string Channel::get_topic()
{
    return this->_topic;
}

bool Channel::get_aut_key()
{
    return this->_aut_key;
}

std::vector<std::string> Channel::get_members()
{
    return this->members;
}

std::vector<std::string> Channel::get_bans_list()
{
    return this->_bans_list;
}

std::map<std::string, int> Channel::get_cannels()
{
    return this->cannels;
}

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

void Channel::set_aut_key(bool aut_key)
{
    this->_aut_key = aut_key;
}

void Channel::set_cannels(std::map<std::string, int> cannels)
{
    this->cannels = cannels;
}

void Channel::add_member(Client &client)
{
    this->members.push_back(client.get_nick());
    this->cannels[client.get_nick()] = 0;
}

void Channel::ban_user(Client &client)
{
    this->_bans_list.push_back(client.get_nick());
}

void Channel::remove_member(Client &client)
{
    std::vector<std::string>::iterator it = this->members.begin();
    while (it != this->members.end())
    {
        if (*it == client.get_nick())
        {
            this->members.erase(it);
            break;
        }
        it++;
    }
}

void Channel::unban_user(Client &client)
{
    std::vector<std::string>::iterator it = this->_bans_list.begin();
    while (it != this->_bans_list.end())
    {
        if (*it == client.get_nick())
        {
            this->_bans_list.erase(it);
            break;
        }
        it++;
    }
}

bool Channel::is_banned(Client &client)
{
    std::vector<std::string>::iterator it = this->_bans_list.begin();
    while (it != this->_bans_list.end())
    {
        if (*it == client.get_nick())
            return true;
        it++;
    }
    return false;
}

bool Channel::is_member(Client &client)
{
    std::vector<std::string>::iterator it = this->members.begin();
    while (it != this->members.end())
    {
        if (*it == client.get_nick())
            return true;
        it++;
    }
    return false;
}


bool    Channel::channel_exists(std::string name)
{
    std::map<std::string, int>::iterator it = this->cannels.begin();
    while (it != this->cannels.end())
    {
        if (it->first == name)
            return true;
        it++;
    }
    return false;
}

// void Channel::broadcast_message(std::string message, std::string sender)
// {
//     std::vector<std::string>::iterator it = this->members.begin();
//     while (it != this->members.end())
//     {
//         if (*it != sender)
//             send_message(message, *it);
//         it++;
//     }
// }

