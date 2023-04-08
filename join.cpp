/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 08:05:10 by waelhamd          #+#    #+#             */
/*   Updated: 2023/04/08 06:14:06 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"headers.hpp"


std::string server::join_response(std::vector<std::string> split, Client &client)
{
	std::string channel;
	std::string response;
	Channel mychannel;
	
	if(split.size() < 2)
		return ("461 JOIN :Not enough parameters\n");
	else if(split.size() >= 2)
	{
		std::vector<std::string> names;
		std::vector<std::string> key;
		names = ft_split(split[1], ',');
		if(split.size() > 2)
			key = ft_split(split[1], ',');
		for(size_t i = 0; i < names.size(); i++)
		{
			if(names[i][0] != '#')
				return ("403 " + names[i] + " :No such channel\n");
			else if(client.get_channel(names[i]))
				return ("443 " + names[i] + " :is already on channel\n");
			else
			{
				client.set_channel(names[i]);
				if(!this->_channels.count(names[i]))
				{//if channel does not exist
					if(key.size() > i)
					{//if key is provided
						mychannel = Channel(names[i], key[i], true);
						mychannel.add_member(client.get_fd());
						mychannel.add_moderator(client.get_fd());
						
					}
					else
					{//if key is not provided
						mychannel = Channel(names[i], "", false);
						mychannel.add_member(client.get_fd());
						mychannel.add_moderator(client.get_fd());
					}
					this->_channels.insert(std::pair<std::string, Channel>(names[i], mychannel));
					std::cout<<"channel created"<<std::endl;
				}
				else
				{//if channel exists
					if(key.size() > i)
					{//if key is provided
						if(this->_channels[names[i]].get_pass() == key[i])
						{
							this->_channels[names[i]].add_member(client.get_fd());
							this->_channels[names[i]].add_moderator(client.get_fd());
						}
						else
							return ("475 " + names[i] + " :Cannot join channel (+k)\n");
					}
					else
					{//if key is not provided
						if(this->_channels[names[i]].get_pass() == "")
						{
							this->_channels[names[i]].add_member(client.get_fd());
							this->_channels[names[i]].add_moderator(client.get_fd());
						}
						else
							return ("475 " + names[i] + " :Cannot join channel (+k)\n");
					}
				}
				//check if user is in ban list
				//check if user is in invite list
				//check if user is in quiet list
				//check if user is in operator list
				
			}
		}
	}
	else if(split.size() > 3)
		return ("461 JOIN :Too many parameters\n");
	
	return ("");
}