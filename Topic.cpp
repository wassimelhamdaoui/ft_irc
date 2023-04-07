#include "headers.hpp"

std::string change_topic(std::string request, Client &client, Channel &channel)
{
    std::vector<std::string> tokens;
    std::string response = "";

    tokens = ft_split(request, ' ');
    // clear topic
    if (tokens[0] == "TOPIC" && tokens.size() == 3 && tokens[tokens.size() - 1] == ":")
    {
        if (!has_comma(tokens[1]))
        {
            if (channel.channel_exists(tokens[1]) == true)
            {
                if (channel.is_member(client) == false)
                    return (response = "<" + client.get_nick() + "> <" + tokens[1] + "> :You're not on that channel\r\n");
                if (channel.is_moderator(client) == false)
                    return (response = "<" + client.get_nick() + "> <" + tokens[1] + "> :You're not a operator\r\n");
                channel.set_topic("");
                response = client.get_nick() + " has cleared the topic of " + tokens[1] + "\r\n";
                channel.broadcast_message(response, client.get_nick());
            }
            else
                return (response = "<" + client.get_nick() + "> <" + tokens[1] + "> :No such channel\r\n");
        }
        // clear topic for multichannel
        else if (has_comma(tokens[1]))
        {
            std::vector<std::string> channels = ft_split(tokens[1], ',');
            for (size_t i = 0; i < channels.size(); i++)
            {
                if (channel.channel_exists(channels[i]) == true)
                {
                    if (channel.is_member(client) == false)
                        return (response = "<" + client.get_nick() + "> <" + channels[i] + "> :You're not on that channel\r\n");
                    if (channel.is_moderator(client) == false)
                        return (response = "<" + client.get_nick() + "> <" + channels[i] + "> :You're not a operator\r\n");
                    channel.set_topic("");
                    response += client.get_nick() + " has cleared the topic of " + channels[i] + "\r\n";
                    channel.broadcast_message(response, client.get_nick());
                }
                else
                    return (response = "<" + client.get_nick() + "> <" + channels[i] + "> :No such channel\r\n");
            }
        }
        
    }
    else if (tokens[0] == "TOPIC" && tokens.size() > 0)
    {
        if (tokens.size() == 1)
            return (response = "<" + client.get_nick() + ">  <" + tokens[0] + "> :Not enough parameters\r\n");
        else if (tokens.size() == 2)
        {
            if (channel.channel_exists(tokens[1]) == true)
            {
                if (channel.is_member(client) == false)
                    return (response = "<" + client.get_nick() + "> <" + tokens[1] + "> :You're not on that channel\r\n");
                return (response = "Topic Of " + tokens[1] + " is:" + channel.get_topic() + "\r\n");
            }
            else
                return (response = "<" + client.get_nick() + "> <" + tokens[1] + "> :No such channel\r\n");
        }
        else if (tokens.size() >= 3)
        {
            if (has_comma(tokens[1]) && tokens.size() == 2)
            {
                std::vector<std::string> channels = ft_split(tokens[1], ',');
                // send topic of each channel to client
                for (size_t i = 0; i < channels.size(); i++)
                {
                    if (channel.channel_exists(channels[i]) == true)
                    {
                        if (channel.is_member(client) == false)
                            return (response = "<" + client.get_nick() + "> <" + channels[i] + "> :You're not on that channel\r\n");
                        response += "Topic Of " + channels[i] + " is:" + channel.get_topic() + "\r\n";
                        send(client.get_fd(), response.c_str(), response.size(), 0);
                        response.clear();
                    }
                    else
                        return (response = "<" + client.get_nick() + "> <" + channels[i] + "> :No such channel\r\n");
                }
            }
            else if (has_comma(tokens[1]) && tokens.size() == 3)
            {
                std::vector<std::string> channels = ft_split(tokens[1], ',');
                // change topic of each channel
                for (size_t i = 0; i < channels.size(); i++)
                {
                    if (channel.channel_exists(channels[i]) == true)
                    {
                        if (channel.is_member(client) == false)
                            return (response = "<" + client.get_nick() + "> <" + channels[i] + "> :You're not on that channel\r\n");
                        if (channel.is_moderator(client) == false)
                            return (response = "<" + client.get_nick() + "> <" + channels[i] + "> :You're not an operator\r\n");
                        channel.set_topic(tokens[2]);
                        response += "Topic Of " + channels[i] + " is:" + channel.get_topic() + "\r\n";
                        channel.broadcast_message(response, client.get_nick());
                        response.clear();
                    }
                    else
                        return (response = "<" + client.get_nick() + "> <" + channels[i] + "> :No such channel\r\n");
                }
            }
            else if (!has_comma(tokens[1]) && tokens.size() == 3)
            {
                if (channel.channel_exists(tokens[1]) == true)
                {
                    if (channel.is_member(client) == false)
                        return (response = "<" + client.get_nick() + "> <" + tokens[1] + "> :You're not on that channel\r\n");
                    if (channel.is_moderator(client) == false)
                        return (response = "<" + client.get_nick() + "> <" + tokens[1] + "> :You're not an operator\r\n");
                    channel.set_topic(tokens[2]);
                    response += "Topic Of " + tokens[1] + " is:" + channel.get_topic() + "\r\n";
                    channel.broadcast_message(response, client.get_nick());
                    response.clear();
                }
                else
                    return (response = "<" + client.get_nick() + "> <" + tokens[1] + "> :No such channel\r\n");
            }
            else
                return (response = "<" + client.get_nick() + ">" + " :Invalid parmeter\r\n");
        }
    }
    return response;
}