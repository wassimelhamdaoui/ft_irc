/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 08:15:16 by mabdelba          #+#    #+#             */
/*   Updated: 2023/04/16 06:49:01 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

std::string 	server::kick_response(std::vector<std::string> split, Client &client)
{
	std::string comment = "";
	int			flg = 0;

	if(client.get_print())
	{
		if(split.size() < 3)
			return (":localhost 461 " + client.get_nick() + " KICK :Not enough parameters\r\n");
		if(!this->_channels.count(split[1]))
			return (":localhost 403 " + client.get_nick() + " " + split[1] + " :No such channel\r\n");
		Channel &channel = this->_channels[split[1]];
		if(!check_inVect(channel.get_members(), client.get_fd()))
			return ("localhost 442 " + client.get_nick() + " " + channel.get_name() + " :You're not on that channel\r\n");
		if(!check_inVect(channel.get_moderators(), client.get_fd()))
			return (":localhost 482 " + client.get_nick() + " " + channel.get_name() + " :You're not channel operator\r\n");
		int ClientFd = getClientFd(this->_map, split[2]);
		if(!ClientFd || !check_inVect(channel.get_members(), ClientFd))
			return (":localhost 441 " + client.get_nick() + " " + split[2] + " " + split[1] + " : They aren't on that channel\r\n");
		if(split.size() > 3 && split[3][0] == ':')
		{
			flg = 1;
			for(size_t i = 3; i < split.size(); i++)
			{
				comment += split[i];
				if(i != split.size() - 1)
					comment += " ";
			}
			comment.erase(comment.find(':'), 1);
		}
		Client &User = this->_map[ClientFd];
		channel.remove_member(ClientFd);
		channel.remove_moderator(ClientFd);
		User.remove_channel(channel.get_name());
		std::string msg = "";
		if(flg)
			msg = " using \"" + comment + "\" as the reason (comment).";
		std::string broad1, broad2;
		broad1 = client.get_nick() + "!~" + client.get_userName() + "@localhost KICK " + User.get_nick() + " out of";
		broad2 = channel.get_name() + msg +"\r\n";
		channel.broad_message(":" + client.get_nick() + "!~" + client.get_userName() + "@localhost KICK " + User.get_nick() + " out of " + channel.get_name() + msg +"\r\n", client.get_fd());
		return (":" + client.get_nick() + "!~" + client.get_userName() + "@localhost KICK " + User.get_nick() + " out of " + channel.get_name() + msg +"\r\n");
	}
	return "";
}