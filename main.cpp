#include "headers.hpp"

void    ft_replace(std::string &str, char c, std::string rep)
{
    size_t pos = str.find(c);
	while(pos != std::string::npos)
	{
		str.replace(pos, 1, rep);
		pos = str.find('\t');
	}
}

std::vector<std::string> modifier(std::string str)
{
    std::vector<std::string> split;
    ft_replace(str, '\t', " ");
    ft_replace(str, '\r', " ");
    ft_replace(str, '\n', " ");
    split = ft_split(str, ' ');

    return split;
}

void    server::parse_request(char *read, int fd, fd_set *master)
{
    Client client(fd);
    std::string request(read);
    std::string response;
    std::vector<std::string> split;

    if(this->_map.count(fd) <= 0)
        this->_map.insert(std::make_pair(fd, client));
    split = modifier(request);
    if(split.empty())
        response = "";
    else if(split[0] == "PASS")
        response = pass_response(split, this->_map[fd]);
    else if(split[0] == "USER")
        response = user_response(split, this->_map[fd]);
    else if(split[0] == "NICK")
        response = nick_response(split, this->_map[fd]);
    else if(split[0] == "JOIN" )
        response = join_response(split, this->_map[fd]);
    else if (split[0] == "PART")
        response = part_response(split, this->_map[fd]);
    else if (split[0] == "TOPIC")
        response = topic_response(split, this->_map[fd]);
    else if(split[0] == "INVITE")
        response = invite_response(split, this->_map[fd]);
    else if (split[0] == "QUIT")
        quit_response(split, this->_map[fd], master);
    else if (split[0] == "PRIVMSG")
        response = privmsg_response(request, this->_map[fd]);
    else
        response = "ircserv: command not found\n";

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