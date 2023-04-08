/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:33:30 by mabdelba          #+#    #+#             */
/*   Updated: 2023/04/08 03:00:57 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"


std::string server::user_response(std::string buff, Client &client)
{
	std::vector<std::string> split;

	split = ft_split(buff, ' ');
	if(split[0] == "USER")
	{
		if(client.get_auth())
			return(ft_message(client.get_nick(), "", "You may not reregister", 0));
		if(split.size() < 5) // || split[1].length() != USERLEN
			return(ft_message(client.get_nick(), "USER", "Not enough parameters", 1));
		if(split[1][0] != '~')
			return(ft_message(client.get_nick(), "USER", "Username must be started by ~", 1));
		client.set_userName(split[1]);
		client.set_auth(true);
		if(client.get_reg() && !client.get_print())
		{
			client.set_print(true);
			return(client.get_nick() +  ": You are successfully regeistred\n");
		}
	}
	
	return(join_response(buff, client));
}


// std::string server::check_authentication(std::string buff, Client &client)
// {
// 	std::vector<std::string> split;
// 	split = ft_split(buff, ' ');
// 	if(!split.empty() && split[0] != "NICK")
// 		return("you must enter your nickname to complete your registration\n");
// 	if()
// 	return("");
// }