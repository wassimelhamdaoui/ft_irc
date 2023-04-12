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
		bool		_inviteMode;

		std::vector<int>			members;
		std::vector<int>			_moderators;
		std::vector<std::string>	_bans_list;
		std::vector<std::string>	_invited_list;
	public:
		//constructors
		Channel();
		Channel(std::string name, std::string pass);
		~Channel();
		//getters
		std::string get_name() const;
		std::string get_pass() const;
		std::string get_topic() const;
		bool 		get_inviteMode() const;
		bool		get_is_private() const;
		std::vector<int> get_members() const;
		//setters
		void set_name(std::string name);
		void set_pass(std::string pass);
		void set_topic(std::string topic);
		void set_inviteMode(bool inviteMode);
		void set_is_private(bool is_private);

		//methods
		void add_member(int fd);
		void add_moderator(int fd);
		void add_invited_list(std::string nick);


		bool is_invited(std::string nick);

		// for part
		bool channel_exist(std::map<std::string, Channel> &channels, std::string channel_name);
		bool is_member(int fd);
		bool is_moderator(int fd);
		void remove_member(int fd);
		void broadcast_message(std::string message, std::string nick, int fd);
		bool is_empty() const;
};

#endif 