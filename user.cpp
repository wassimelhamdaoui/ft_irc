/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:33:30 by mabdelba          #+#    #+#             */
/*   Updated: 2023/04/08 03:08:52 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"


std::string server::user_response(std::vector<std::string> split, Client &client)
{
	if(client.get_pass())
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
	return("");
}
