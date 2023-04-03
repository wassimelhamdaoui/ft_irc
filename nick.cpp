/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:22:03 by mabdelba          #+#    #+#             */
/*   Updated: 2023/04/02 23:33:40 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

bool check_double(std::vector<std::string> vect, std::string str)
{
	if(vect.size() >= 0)
	{
		for(size_t i = 0; i < vect.size(); i++)
		{
			if(str == vect[i])
				return true;
		}
	}
	return false;
}

bool check_nickname(std::string nick)
{
	if(nick.size() > 9)
		return false;
	return true;
}

std::string server::nick_response(std::string buff, Client &client)
{
	std::vector<std::string> split;
	
	split = ft_split(buff, ' ');
	if(client.get_pass() && !split.empty())
	{
		if(split[0] != "USER" && split[0] != "NICK")
			return ("you must enter <NICK> <USER>\n");
		else if(split[0] == "NICK" && split.size() < 2)
			return ("<NICK> <nickname> :No nickname given\n");
		else if(!check_nickname(split[1]))	
			return ("<client> <nick> :Erroneus nickname\n");
		else if(check_double(this->_nickname, split[1]))
			return("<client> <nick> :Nickname is already in use\n");
		this->_nickname.push_back(split[1]);
		client.set_nick(split[1]);
	}
	return ("");
}
