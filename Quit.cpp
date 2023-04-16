# include "headers.hpp"

std::string server::quit_response(std::vector<std::string> split, Client &client, fd_set *master)
{
    std::string response;
    std::string name = client.get_nick();

    if (name == "")
        name = "0.0.0.0";
    if (split.size() == 2 && split[1] == ":")
        response = "ERROR :Closing Link: 0.0.0.0 (Quit: )\r\n";
    else if (split.size() > 1)
    {
        std::string reason;
        std::vector<std::string>::iterator it = split.begin();
        ++it;
        for (; it != split.end(); it++)
        {
            reason += *it;
            reason += " ";
        }
        if (has_semi_colon(split[1]) == true)
        {
            size_t pos;
            while ((pos = reason.find(':')) != std::string::npos)
                    reason.erase(pos, 1);
            response = "ERROR :Closing Link:" + name + " (Quit: " + reason +")\r\n";
        }
        else
            response = "ERROR :Closing Link: 0.0.0.0 (Quit: " + split[1] + ")\r\n";
    }
    send(client.get_fd(), response.c_str(), response.size(), 0);
    close(client.get_fd());
    FD_CLR(client.get_fd(), master);
    return (response);
}