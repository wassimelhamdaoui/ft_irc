#include "headers.hpp"


std::string server::clear_topic(std::string token, Client &client)
{
    if(!client.get_print())
		return ("451 :You have not registered\n");
    std::string response = "";
    if (this->_channels.count(token) > 0)
    {
        if (this->_channels[token].is_member(client.get_fd()) == false)
            return (response = "<" + client.get_nick() + "> <" + token + "> :You're not on that channel\r\n");
        if (this->_channels[token].is_moderator(client.get_fd()) == false)
            return (response = "<" + client.get_nick() + "> <" + token + "> :You're not a operator\r\n");
        if (this->_channels[token].get_topic().empty())
            return (response = "<" + client.get_nick() + "> <" + token + "> :No topic is set\r\n");
        this->_channels[token].set_topic("");
        if (this->_channels[token].get_members().size() != 0)
        {
            std::vector<int> members = this->_channels[token].get_members();
            for (size_t i = 0; i < members.size(); i++)
                send(members[i], response.c_str(), response.size(), 0);
        }
    }
    else
        return (response = "<" + client.get_nick() + "> <" + token + "> :No such channel\r\n");
    return (response);
}


std::string server::know_topic(std::string token, Client &client)
{
    std::string response = "";
    if (this->_channels.count(token) > 0)
    {
        if (this->_channels[token].is_member(client.get_fd()) == false)
            return (response = "<" + client.get_nick() + "> <" + token + "> :You're not on that channel\r\n");
        if (this->_channels[token].get_topic().empty())
            return (response = "<" + client.get_nick() + "> <" + token + "> :No topic is set\r\n");
        response = "<" + client.get_nick() + "> topic of <" + token + "> is:" + this->_channels[token].get_topic() + "\r\n";
    }
    else
        return (response = "<" + client.get_nick() + "> <" + token + "> :No such channel\r\n");
    return (response);
}

std::string server::set_topic(std::string token, std::string topic, Client &client)
{
    std::string response = "";
    if (this->_channels.count(token) > 0)
    {
        if (this->_channels[token].is_member(client.get_fd()) == false)
            return (response = "<" + client.get_nick() + "> <" + token + "> :You're not on that channel\r\n");
        if (this->_channels[token].is_moderator(client.get_fd()) == false)
            return (response = "<" + client.get_nick() + "> <" + token + "> :You're not an operator\r\n");
        this->_channels[token].set_topic(topic);
        if (this->_channels[token].get_members().size() != 0)
        {
            response = "<" + client.get_nick() + "> change <" + token + "> topic to: " + this->_channels[token].get_topic() + "\r\n";
            std::vector<int> members = this->_channels[token].get_members();
            for (size_t i = 0; i < members.size(); i++)
                send(members[i], response.c_str(), response.size(), 0);
            response.clear();
        }
    }
    else
        return (response = "<" + client.get_nick() + "> <" + token + "> :No such channel\r\n");
    return (response);
}

std::string server::topic_response(std::vector<std::string> tokens, Client &client)
{
    std::string response = "";

    // clear topic
    if (tokens[0] == "TOPIC" && tokens.size() == 3 && tokens[tokens.size() - 1] == ":")
    {
        if (!has_comma(tokens[1]))
            response = clear_topic(tokens[1], client);
        // clear topic for multichannel
        else if (has_comma(tokens[1]))
        {
            std::vector<std::string> channels = ft_split(tokens[1], ',');
            for (size_t i = 0; i < channels.size(); i++)
                response += clear_topic(channels[i], client);
        }
    }

    else if (tokens[0] == "TOPIC" && tokens.size() > 0)
    {
        if (tokens.size() == 1)
            return (response = "<" + client.get_nick() + ">  <" + tokens[0] + "> :Not enough parameters\r\n");
        // know topic
        else if (tokens.size() == 2)
        {
            if (!has_comma(tokens[1]))
                response = know_topic(tokens[1], client);
            // know topic for multichannel
            else if (has_comma(tokens[1]))
            {
                std::vector<std::string> channels = ft_split(tokens[1], ',');
                for (size_t i = 0; i < channels.size(); i++)
                    response += know_topic(channels[i], client);
            }
        }
        else if (tokens.size() >= 3)
        {
            if (!has_comma(tokens[1]) && tokens.size() == 3)
                response = set_topic(tokens[1], tokens[2], client);
            else if (has_comma(tokens[1]) && tokens.size() == 3)
            {
                std::vector<std::string> channels = ft_split(tokens[1], ',');
                for (size_t i = 0; i < channels.size(); i++)
                    response += set_topic(channels[i], tokens[2], client);
            }
            else
                return (response = "<" + client.get_nick() + ">" + " :Invalid parmeter\r\n");
        }
    }
    return response;
}