#include "headers.hpp"

std::string server::part1(std::string token, Client &client)
{
    std::string response = "";
    if (this->_channels.count(token) > 0)
    {
        if (this->_channels[token].is_member(client.get_fd()) == false)
            return (response = ":localhost 442 " + client.get_nick() + " " + token + " :You're not on that channel\r\n");
        this->_channels[token].remove_member(client.get_fd());
        client.remove_channel(token);
        if (this->_channels[token].get_members().size() == 0)
            this->_channels.erase(token);
        response = ":" + client.get_nick() + " PART " + token + "\r\n";
        if (this->_channels.size() != 0)
        {
            std::vector<int> members = this->_channels[token].get_members();
            for (size_t i = 0; i < members.size(); i++)
            {
                if (members[i] != client.get_fd())
                    send(members[i], response.c_str(), response.size(), 0);
            }
            if (this->_channels[token].get_members().size() == 0)
                this->_channels.erase(token);
        }
        response = "";
    }
    else
        return (response = ":localhost 403 " + client.get_nick() + " PART " + " :No such channel\r\n");
    return (response);
}

std::string server::part_with_reason(std::string token, Client &client, std::string reason)
{
    std::string response = "";
    if (this->_channels.count(token) > 0)
    {
        if (this->_channels[token].is_member(client.get_fd()) == false)
            return (response = ":localhost 442 " + client.get_nick() + " " + token + " :You're not on that channel\r\n");
        this->_channels[token].remove_member(client.get_fd());
        client.remove_channel(token);
        if (this->_channels[token].get_members().size() == 0)
            this->_channels.erase(token);
        response = ":" + client.get_nick() + " PART " + token + " :" + reason + "\r\n";
        if (reason.empty())
            response = ":" + client.get_nick() + " PART " + token + "\r\n";
        if (this->_channels.size() != 0)
        {
            std::vector<int> members = this->_channels[token].get_members();
            for (size_t i = 0; i < members.size(); i++)
            {
                if (members[i] != client.get_fd())
                    send(members[i], response.c_str(), response.size(), 0);
            }
            if (this->_channels[token].get_members().size() == 0)
                this->_channels.erase(token);
        }
        response = "";
    }
    else
        return (response = ":localhost 403 " + client.get_nick() + " PART " + " :No such channel\r\n");
    return (response);
}

std::string server::part_response(std::vector<std::string> tokens, Client &client)
{
    // if(!client.get_print())
	// 	return (":localhost 451 * PART :You must finish connecting with nickname first.\r\n");
    std::string response = "";
    if(!client.get_print())
		return ("451 :You have not registered\n");
    if (tokens[0] == "PART" && tokens.size() > 0)
    {
        if (tokens.size() == 1)
            return (response = ":localhost 461 " + client.get_nick() + " " + tokens[0] + " :Not enough parameters\r\n");
        else if (tokens.size() == 2)
        {
            if (has_comma(tokens[1]))
            {
                std::vector<std::string> channels = ft_split(tokens[1], ',');
                for (size_t i = 0; i < channels.size(); i++)
                    response = this->part1(channels[i], client);
            }
           if (!has_comma(tokens[1]))
                response = this->part1(tokens[1], client);
        }
        else if (tokens.size() >= 3)
        {
            std::string reason = tokens[2];
            if (has_semi_colon(tokens[2]) == false)
            {
                reason = "";
                std::vector<std::string>::iterator it = tokens.begin();
                it += 2;
                for (; it != tokens.end(); it++)
                    reason += *it + " ";
            }
            if (has_comma(tokens[1]))
            {
                std::vector<std::string> channels = ft_split(tokens[1], ',');
                for (size_t i = 0; i < channels.size(); i++)
                        response = this->part_with_reason(channels[i], client, reason);
            }
            if (has_comma(tokens[1]) == false && tokens.size() == 3)
                response = this->part_with_reason(tokens[1], client, reason);
        }
    }
    return response;
}

