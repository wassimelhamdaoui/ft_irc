#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "Client.hpp"
#include "headers.hpp"

// class Client;

class Channel
{
	private:
		std::string _name;
		std::string _pass;
		std::string _topic;
		bool		_is_private;
		bool 		invite_only;

		std::vector<int>			members;
		std::vector<int>			_moderators;
		std::vector<std::string>	_bans_list;
		std::vector<std::string>	_invited_list;
	public:
		//constructors
		Channel();
		Channel(std::string name, std::string pass);
		Channel(const Channel &copy);
		Channel &operator=(const Channel &copy);
		~Channel();
		//getters
		std::string get_name() const;
		std::string get_pass() const;
		std::string get_topic() const;
		bool 		get_invite_only() const;
		bool		get_is_private() const;
		std::vector<int> get_members() const;
		//setters
		void set_name(std::string name);
		void set_pass(std::string pass);
		void set_topic(std::string topic);
		void set_invite_only(bool invite_only);
		void set_is_private(bool is_private);
		//methods
		void add_member(int fd);
		void add_moderator(int fd);
		bool is_invited(std::string nick);

};

#endif 