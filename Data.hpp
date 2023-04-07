#ifndef DATA_HPP
# define DATA_HPP

#include"Channel.hpp"
#include"Client.hpp"
#include "server.hpp"
# include "headers.hpp"

class Channel;

class Data
{
	private:
		static std::map<std::string, Channel> 					channels;//<channel name, channel>
		static std::map<std::string, int> 						clients;//<nickname, fd>

	public:

		Data();
		Data( Data const & src );
		~Data();
};

#endif