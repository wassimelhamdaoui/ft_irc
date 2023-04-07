#include "headers.hpp"

std::string part_response(std::string request, Client &client, Channel &channel)
{
    std::vector<std::string> tokens;
    std::string response;

    tokens = ft_split(request, ' ');
    if (tokens[0] == "PART" && tokens.size() > 0)
    {
        if (tokens.size() == 1)
            return (response = "<" + client.get_nick() + ">  <" + tokens[0] + "> :Not enough parameters\r\n");
        else if (tokens.size() == 2)
        {
            if (channel.channel_exists(tokens[1]) == true)
            {
                if (channel.is_member(client) == false)
                    return (response = "<" + client.get_nick() + "> <" + tokens[1] + "> :You're not on that channel\r\n");
                channel.remove_member(client);
                if (channel.get_members().size() == 0)
                    channel.remove_channel(tokens[1]);
                response = client.get_nick() + " has left " + tokens[1] + "\r\n";
                channel.broadcast_message(response, client.get_nick());
            }
            else
                return (response = "<" + client.get_nick() + "> <" + tokens[1] + "> :No such channel\r\n");

        }
        else if (tokens.size() >= 3)
        {
            if (has_comma(tokens[1]))
            {
                std::vector<std::string> channels = ft_split(tokens[1], ',');
                for (size_t i = 0; i < channels.size(); i++)
                {
                    if (channel.channel_exists(channels[i]) == true)
                    {
                        if (channel.is_member(client) == false)
                            return (response = "<" + client.get_nick() + "> <" + channels[i] + "> :You're not on that channel\r\n");
                        channel.remove_member(client);
                        if (channel.get_members().size() == 0)
                            channel.remove_channel(channels[i]);
                        response += client.get_nick() + " has left " + channels[i] + "\r\n";
                        channel.broadcast_message(response, client.get_nick());
                    }
                    else
                        return (response = "<" + client.get_nick() + "> <" + channels[i] + "> :No such channel\r\n");
                }
            }
            else if (has_comma(tokens[1]) == false && tokens.size() == 3)
            {
                if (channel.channel_exists(tokens[1]) == true)
                {
                    if (channel.is_member(client) == false)
                        return (response = "<" + client.get_nick() + "> <" + tokens[1] + "> :You're not on that channel\r\n");
                    channel.remove_member(client);
                    if (channel.get_members().size() == 0)
                        channel.remove_channel(tokens[1]);
                    response = client.get_nick() + " has left " + tokens[1] + " Reason: " + tokens[2] + "\r\n";
                    channel.broadcast_message(response, client.get_nick());
                }
                else
                    return (response = "<" + client.get_nick() + "> <" + tokens[1] + "> :No such channel\r\n");
            }
        }
        else
            return (response = "<" + client.get_nick() + "> <" + tokens[0] + "> :Invalid parameters\r\n");
    }
    return response;
}

