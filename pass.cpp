/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:52:15 by mabdelba          #+#    #+#             */
/*   Updated: 2023/04/08 06:26:17 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

std::vector<std::string> ft_split(std::string str, char sep)
{
    std::vector<std::string> res;
    std::string word;
    std::stringstream stream(str);

    for(; std::getline(stream, word, sep); ){
        if (!word.empty())
            res.push_back(word);
    }
    return (res);
}

void    erase_charcter(std::string& str, char c)
{
    size_t pos = str.find(c);
    while(pos != std::string::npos)
    {
        str.erase(pos, 1);
        pos = str.find(c);
    }
}

std::string ft_message(std::string a, std::string b, std::string c, int flg)
{
	std::string ret;
	if(flg == 0)
		ret = "<" + a + "> :" + c + "\n";
	else if(flg == 1)
		ret = "<" + a + "> <" + b +">" " :"  + c + "\n";
	return ret;
}

std::string server::pass_response(std::vector<std::string> split, Client &client)
{
	if(!client.get_pass())
	{
		if(split.size() < 2)
			return(":localhost 461 PASS :Not enough parameters\r\n");
		if(split[1] != this->get_pass())
			return (":localhost 464 PASS :Password incorrect\r\n");
		client.set_pass(true);
		return ("");
	}
	return (":localhost 462 PASS :You may not reregister\r\n");
}


