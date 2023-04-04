#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "headers.hpp"

class Channel
{
	private:
		std::string _name;
		std::string _pass;
		std::string _topic;
		bool  _aut_key;
		std::vector<std::string> members;
		std::vector<std::string> _bans_list;
		std::map<std::string, int> cannels;

	public:

		Channel();
		Channel(std::string name, std::string pass);
		Channel( Channel const & src );

		/**********  Channel methodes *********/
		std::string get_name();
		std::string get_pass();
		std::string get_topic();
		bool get_aut_key();
		std::vector<std::string> get_members();
		std::vector<std::string> get_bans_list();
		std::map<std::string, int> get_cannels();

		void set_name(std::string name);
		void set_pass(std::string pass);
		void set_topic(std::string topic);
		void set_aut_key(bool aut_key);
		void set_cannels(std::map<std::string, int> cannels);

		void add_member(std::string member);
		void ban_user(std::string user);
		void remove_member(std::string member);
		void unban_user(std::string user);
		bool is_banned(std::string user);

		void broadcast_message(std::string message, std::string sender);

		/**********  operator overload *********/

		Channel & operator=( Channel const & rhs );

		/**********  destructor *********/
		~Channel();

};

#endif 