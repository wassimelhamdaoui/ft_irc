#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "Client.hpp"
#include "headers.hpp"

class Client;

class Channel
{
	private:
		std::string _name;
		std::string _pass;
		std::string _topic;
		bool		_is_private;

		std::vector<int>			members;
		std::vector<int>			_moderators;
		std::vector<std::string>	_bans_list;
		std::vector<std::string>	_invited_list;
	public:
		//constructors
		Channel();
		Channel(std::string name, std::string pass, bool is_private);
		Channel(const Channel &copy);
		Channel &operator=(const Channel &copy);
		~Channel();
		//getters
		std::string get_name() const;
		std::string get_pass() const;
		std::string get_topic() const;
		bool		get_is_private() const;
		//setters
		void set_name(std::string name);
		void set_pass(std::string pass);
		void set_topic(std::string topic);
		void set_is_private(bool is_private);
		//methods
		void add_member(int fd);
		void add_moderator(int fd);
};

#endif 