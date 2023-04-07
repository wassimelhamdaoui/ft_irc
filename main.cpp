#include "server.hpp"


std::string change_topic(std::string request, Client &client, Channel &channel)
{
    std::vector<std::string> tokens;
    std::string response = "";

    tokens = ft_split(request, ' ');
    if (tokens[0] == "TOPIC" && tokens.size() > 0)
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
        else if (tokens.size() == 3)
        {
            if (has_comma(tokens[1]) && tokens.size() == 3)
            {
                std::vector<std::string> channels = ft_split(tokens[1], ',');
                // send topic of each channel to client
                if (tokens[1] != ":")
                {
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
                else if (tokens[1] == ":")
                {
                    // remove topic of each channel
                    for (size_t i = 0; i < channels.size(); i++)
                    {
                        if (channel.channel_exists(channels[i]) == true)
                        {
                            if (channel.is_member(client) == false)
                                return (response = "<" + client.get_nick() + "> <" + channels[i] + "> :You're not on that channel\r\n");
                            if (channel.is_moderator(client) == false)
                                return (response = "<" + client.get_nick() + "> <" + channels[i] + "> :You're not an operator\r\n");
                            channel.clear_topic();
                            response += "Topic Of " + channels[i] + " is: removed\r\n";
                            send(client.get_fd(), response.c_str(), response.size(), 0);
                            response.clear();
                        }
                        else
                            return (response = "<" + client.get_nick() + "> <" + channels[i] + "> :No such channel\r\n");
                    }
                }
            }
            else if (has_comma(tokens[1]) && tokens.size() == 3 && tokens[2] != ":")
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
            else if (!has_comma(tokens[1]) && tokens.size() == 3 && tokens[2] != ":")
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

void    server::parse_request(char *read, int fd)
{
    Client client(fd);
    std::string request(read);
    std::string response;
    
    if(this->_map.count(fd) <= 0)
        this->_map.insert(std::make_pair(fd, client));
    
    response = pass_response(request, this->_map[fd]);
    send(fd, response.c_str(), response.size(), 0);
}

int main(int ac, char **av)
{
    try
    {
        if (!is_valid_arg(ac, av))
            return 1;
        std::string str(av[2]);
        server ser(atoi(av[1]), str);
        ser.set_pass(str);
        ser.set_port(atoi(av[1]));
        ser.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}