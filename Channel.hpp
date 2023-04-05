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
		bool  _aut_key;
		bool _is_private;

		std::vector<std::string> members;
		std::vector<std::string> _bans_list;
		std::vector<std::string> _invited_list;
		std::vector<std::string> _moderators;
		std::map<std::string, int> cannels;

	public:

		Channel();
		Channel(std::string name, std::string pass);
		Channel( Channel const & src );

		/**********  getters *********/
		std::string get_name();
		std::string get_pass();
		std::string get_topic();
		bool get_aut_key();
		std::vector<std::string> get_members();
		std::vector<std::string> get_bans_list();
		std::map<std::string, int> get_cannels();

		/**********  setters *********/
		void set_name(std::string name);
		void set_pass(std::string pass);
		void set_topic(std::string topic);
		void set_aut_key(bool aut_key);
		void set_cannels(std::map<std::string, int> cannels);

		void add_member(Client &client);
		void ban_user(Client &client);
		void remove_member(Client &client);
		void unban_user(Client &client);
		bool is_banned(Client &client);
		bool is_member(Client &client);

		void broadcast_message(std::string message, std::string sender);

		/**********  operator overload *********/

		Channel & operator=( Channel const & rhs );

		/**********  member functions *********/

		bool channel_exists(std::string name);

		/**********  destructor *********/
		~Channel();

};

#endif 