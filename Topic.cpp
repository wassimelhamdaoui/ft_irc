#include "headers.hpp"


std::string server::clear_topic(std::string token, Client &client)
{
    if(!client.get_print())
		return (":localhost 451 * TOPIC :You must finish connecting with nickname first.\r\n");
    std::string response = "";
    if (this->_channels.count(token) > 0)
    {
        if (this->_channels[token].is_member(client.get_fd()) == false)
            return (response = ":localhost 442 " + client.get_nick() + " " + token + " :You're not on that channel\r\n");
        if (this->_channels[token].is_moderator(client.get_fd()) == false)
            return (response = ":localhost 482 " + client.get_nick() + " " + token + " :You're not channel operator\r\n");
        if (this->_channels[token].get_topic().empty())
            return (response = ":localhost 331 " + client.get_nick() + " " + token + " :No topic is set\r\n");
        this->_channels[token].set_topic("");
        if (this->_channels[token].get_members().size() != 0)
        {
            response = ":localhost " + client.get_nick() + " Clearing Topic ON " + token + "\r\n";
            std::vector<int> members = this->_channels[token].get_members();
            for (size_t i = 0; i < members.size(); i++)
            {
                if (members[i] != client.get_fd())
                    send(members[i], response.c_str(), response.size(), 0);
            }
        }
    }
    else
        return (":localhost 403 " + client.get_nick() + " TOPIC " + ":No such channel\r\n");
    return (response);
}


std::string server::know_topic(std::string token, Client &client)
{
    std::string response = "";
    if (this->_channels.count(token) > 0)
    {
        if (this->_channels[token].is_member(client.get_fd()) == false)
            return (response = ":localhost 442 " + client.get_nick() + " " + token + " :You're not on that channel\r\n");
        if (this->_channels[token].get_topic().empty())
            return (response = ":localhost 331 " + client.get_nick() + " " + token + " :No topic is set\r\n");
        response = ":localhost 332 " + client.get_nick() + " " + token + " :" + this->_channels[token].get_topic() + ".\r\n";
    }
    else
        return (":localhost 403 " + client.get_nick() + " TOPIC " + ":No such channel\r\n");
    return (response);
}

std::string server::set_topic(std::string token, std::string topic, Client &client)
{
    std::string response = "";
    if (this->_channels.count(token) > 0)
    {
        if (this->_channels[token].is_member(client.get_fd()) == false)
            return (response = ":localhost 442 " + client.get_nick() + " " + token + " :You're not on that channel\r\n");
        if (this->_channels[token].is_moderator(client.get_fd()) == false)
            return (response = ":localhost 482 " + client.get_nick() + " " + token + " :You're not channel operator\r\n");
        this->_channels[token].set_topic(topic);
        if (this->_channels[token].get_members().size() != 0)
        {
            // change topic message
            response = ":localhost 333 " + client.get_nick() + " " + token + " " + client.get_nick() + " :change topic to " + topic + " \r\n";
            std::vector<int> members = this->_channels[token].get_members();
            for (size_t i = 0; i < members.size(); i++)
            {
                if (members[i] != client.get_fd())
                    send(members[i], response.c_str(), response.size(), 0);
            }
            response.clear();
        }
    }
    else
        return (":localhost 403 " + client.get_nick() + " TOPIC " + ":No such channel\r\n");
    return (response);
}

std::string server::topic_response(std::vector<std::string> tokens, Client &client)
{
    // if(!client.get_print())
	// 	return (":localhost 451 * TOPIC :You must finish connecting with nickname first.\r\n");
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
            return (response = ":localhost 461 " + client.get_nick() + " " + tokens[0] + " :Not enough parameters\r\n");
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
            std::string topic = tokens[2];
            if (tokens.size() > 3 && has_semi_colon(tokens[2]))
            {
                for (size_t i = 3; i < tokens.size(); i++)
                    topic += " " + tokens[i];
                size_t pos;
                while ((pos = topic.find(':')) != std::string::npos)
                    topic.erase(pos, 1);
            }
            if (!has_comma(tokens[1]))
                response = set_topic(tokens[1], topic, client);
            else if (has_comma(tokens[1]))
            {
                std::vector<std::string> channels = ft_split(tokens[1], ',');
                for (size_t i = 0; i < channels.size(); i++)
                    response += set_topic(channels[i], topic, client);
            }
        }
    }
    return response;
}