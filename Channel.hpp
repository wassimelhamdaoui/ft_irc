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
		std::string _mode;
		std::string _creation_time;
		int			_limit;
		bool		_is_private;
		bool		_inviteMode;
		bool		_topicMode;
		bool		_limitMode;

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
		std::string get_mode() const;
		int			get_limit() const;

		bool 		get_inviteMode() const;
		bool		get_is_private() const;
		bool		get_topicMode() const;
		bool		get_limitMode() const;
		std::string get_creation_time() const;
		std::vector<int> get_members() const;
		std::vector<int> get_moderators() const;
		//setters
		void set_name(std::string name);
		void set_creation_time(std::string time);
		void set_pass(std::string pass);
		void set_topic(std::string topic);
		void set_mode(std::string mode);
		void set_limit(int limit);
		void set_inviteMode(bool inviteMode);
		void set_is_private(bool is_private);
		void set_topicMode(bool topicMode);
		void set_limitMode(bool limitMode);

		//methods
		void add_member(int fd);
		void add_moderator(int fd);
		void remove_member(int fd);
		void remove_moderator(int fd);
		void add_invited_list(std::string nick);


		bool is_invited(std::string nick);

		// for part
		bool channel_exist(std::map<std::string, Channel> &channels, std::string channel_name);
		bool is_member(int fd);
		bool is_moderator(int fd);
		void broadcast_message(std::string message, int fd);
		bool is_empty() const;
};

#endif 