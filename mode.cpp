/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 06:45:43 by mabdelba          #+#    #+#             */
/*   Updated: 2023/04/15 10:26:07 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

bool str_isdigit(std::string str)
{
    for(int i = 0; str[i]; i++)
    {
        if(!isdigit(str[i]))
            return false;
    }
    return true;
}

std::string 	server::mode_response(std::vector<std::string> split, Client &client)
{
	std::string response;
	int			flg;

	if(client.get_print())
	{
		if(split.size() < 2)
			return (":localhost 461 " + client.get_nick() + " " + split[0] + " :Not enough parameters\r\n");
		if(!this->_channels.count(split[1]))
			return (":localhost 403 " + client.get_nick() +  " " + split[1] + " :No such channel\r\n");
		Channel &channel = this->_channels[split[1]];
		if(split.size() == 2 && check_inVect(channel.get_members(), client.get_fd()))
			return (":localhost 324 " + client.get_nick() + " " + split[1] + " +" + channel.get_mode() + 
					"\n:localhost 329 " + client.get_nick() + " " + split[1] + " " + 
					channel.get_creation_time() + "\r\n");
		if(!check_inVect(channel.get_moderators(), client.get_fd()))
			return (":localhost 482 " + client.get_nick() + " " + split[1] + " :You're not channel operator\r\n");
		std::string mode = channel.get_mode();
		flg = 0;
		response = ":" + client.get_nick() + "!~" + client.get_userName() + "@localhost MODE " + channel.get_name();
		if(split[2][0] == '+')
		{
			response += " +";
			for(int i = 1; split[2][i]; i++)
			{
				char c = split[2][i];
				if(c == 'i' && !channel.get_inviteMode())
				{
					channel.set_inviteMode(true);
					mode += "i";
					response += "i";
					flg++;
				}
				if(c == 't' && !channel.get_topicMode())
				{
					channel.set_topicMode(true);
					mode += "t";
					response += "t";
					flg++;
				}
				if(c == 'k' && !channel.get_is_private() && split.size() >= 4)
				{
					std::string key = split[3];
					channel.set_is_private(true);
					channel.set_pass(key);
					mode += "k " + key + " ";
					response += "k " + key + " ";
					flg++;
				}
				if(c == 'l' && !channel.get_limitMode() && split.size() >= 4 && str_isdigit(split[3]))
				{
					int limit = atoi(split[3].c_str());
					if((size_t)limit < channel.get_members().size())
						limit = (int)channel.get_members().size();
					channel.set_limitMode(true);
					channel.set_limit(limit);
					mode += "l " + std::to_string(limit) + " ";
					response += "l " + std::to_string(limit) + " ";
					flg++;
				}
			}
		}
		else if(split[2][0] == '-')
		{
			response += " -";
			for(int i = 1; split[2][i]; i++)
			{
				char c = split[2][i];
				if(c == 'i' && channel.get_inviteMode())
				{
					channel.set_inviteMode(false);
					mode.erase(mode.find('i'), 1);
					response += "i";
					flg++;
				}
				if(c == 't' && channel.get_topicMode())
				{
					channel.set_topicMode(false);
					mode.erase(mode.find('t'), 1);
					response += "t";
					flg++;
				}
				if(c == 'k' && channel.get_is_private() && split.size() >= 4)
				{
					std::string oldkey = channel.get_pass();
					std::string key = split[3];
					channel.set_is_private(false);
					channel.set_pass("");
					mode.erase(mode.find("k " + oldkey + " "), oldkey.length( ) + 3);
					response += "k " + key;
					flg++;
				}
				if(c == 'l' && channel.get_limitMode())
				{
					std::string limit = std::to_string(channel.get_limit());
					channel.set_limitMode(false);
					channel.set_limit(CHANMAX);
					mode.erase(mode.find("l " + limit + " "), limit.length( ) + 3);
					response += "l" ;
					flg++;
				}				
			}
		}
		channel.set_mode(mode);
		if(flg)
			return (response + "\r\n");
	}
	return "";
}
