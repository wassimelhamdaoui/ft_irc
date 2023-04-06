#include "server.hpp"

// void    create_channel(std::string name, std::string pass, Channel &channel,Client client)
// {
//     channel.set_name(name);
//     channel.set_pass(pass);
//     channel.add_member(client);
//     channel.set_topic("No topic is set");
//     channel.set_aut_key(true);
//     channel.get_cannels()[name] = 1;
// }

// std::string join_response(std::string request, Client &client, Channel &channel)
// {
//     std::vector<std::string> tokens;
//     std::string response;

//     tokens = ft_split(request, ' ');
//     if (tokens.size() != 3)
//     {
//         response = "<" + client.get_nick() + "> <" + tokens[0] + "> :Not enough parameters\r\n";
//         return response;
//     }
//     // if (tokens.size() > 3)
//     // {
//     //     response = join_multiple_channels(tokens, client);
//     //     return response;
//     // }
//     if (channel.channel_exists(tokens[1]) == false && (tokens.size() == 3))
//         create_channel(tokens[1], tokens[2], channel, client);
//     else
//         response = client.get_nick() + " has joined " + tokens[1] + "\r\n";
//     return response;
// }


bool has_comma(std::string str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == ',')
            return true;
    }
    return false;
}

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

void    server::parse_request(char *read, int fd)
{
    Client client(fd);
    Channel channel;
    std::string request(read);
    std::string response;
    std::vector<std::string> tokens;
    std::string error = "ERROR: Invalid command\r\n";

    if(this->_map.count(fd) <= 0)
        this->_map.insert(std::make_pair(fd, client));
    tokens = ft_split(request, ' ');
    if (tokens[0] == "PASS")
        response = pass_response(request, this->_map[fd]);
    else if (tokens[0] == "PART")
        response = part_response(request, this->_map[fd], channel);
    // else if (tokens[0] == "NICK" && response == "" && this->_map[fd].get_auth() == true)
    //     response = nick_response(request, this->_map[fd]);
    // else if (tokens[0] == "JOIN" )
    //     response = join_response(request, this->_map[fd], channel);
    else
        response = error;
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