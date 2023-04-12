/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 08:05:10 by waelhamd          #+#    #+#             */
/*   Updated: 2023/04/12 08:49:01 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"headers.hpp"


std::string server::join_response(std::vector<std::string> split, Client &client)
{
	if(!client.get_print())
		return (":localhost 451 * JOIN :You must finish connecting with nickname first.\r\n");
	Channel mychannel;
	if(split.size() < 2)
		return(":localhost 461 " + client.get_nick() + " " + split[0] + " :Not enough parameters\r\n");
	else if(split.size() >= 2)
	{
		std::vector<std::string> names;
		std::vector<std::string> key;
		names = ft_split(split[1], ',');
		if(split.size() > 2)
			key = ft_split(split[2], ',');
		for(size_t i = 0; i < names.size(); i++)
		{
			if(names[i][0] != '#' && names[i].length() > 1)
				return (":localhost 403 " + client.get_nick() + " JOIN " + ":No such channel\r\n");
			else if(client.check_member(names[i]))
				return (":localhost 443 " + client.get_nick() + " " + names[i] + ":is already on channel\r\n");
			else
			{
				if(!this->_channels.count(names[i]))
				{//if channel does not exist
					client.set_channel(names[i]);
					if(key.size() > i)
						mychannel = Channel(names[i], key[i]);//if key is provided
					else 
						mychannel = Channel(names[i], "");//if key is not provided

					mychannel.add_member(client.get_fd());
					mychannel.add_moderator(client.get_fd());
					this->_channels.insert(make_pair(names[i], mychannel));
				}
				else
				{//if channel exists
					//check if the moderator is part of the channel need to chanage moderator
					if(this->_channels[names[i]].get_inviteMode())
					{
						if(this->_channels[names[i]].is_invited(client.get_nick()))
						{
							client.set_channel(names[i]);
							this->_channels[names[i]].add_member(client.get_fd());
							//need to notify other users in channel that user has joined
						}
						else
							return (":localhost 473 " + client.get_nick() + " " + names[i] + " :Cannot join channel (+i)\r\n");
					}
					else
					{
						if(key.size() > i)
						{//if key is provided
							if(this->_channels[names[i]].get_pass() == key[i])
							{
								client.set_channel(names[i]);
								this->_channels[names[i]].add_member(client.get_fd());
							}
							else
								return (":localhost 475 " + client.get_nick() + " " + names[i] + " :Cannot join channel (+k)\r\n");
						}
						else
						{//if key is not provided
							if(this->_channels[names[i]].get_pass() == "")
							{
								client.set_channel(names[i]);
								this->_channels[names[i]].add_member(client.get_fd());
							}
							else
								return (":localhost 475 " + client.get_nick() + " " + names[i] + " :Cannot join channel (+k)\r\n");
						}
					}
					
				}
			}
		}
	}
	else if(split.size() > 3)
		return (":localhost 461 " + client.get_nick() + " " + split[0] + " :Too many parameters\r\n");
	
	return ("");
}