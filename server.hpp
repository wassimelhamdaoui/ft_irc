#ifndef SERVER_HPP
# define SERVER_HPP

#define USERLEN 12
#include "headers.hpp"

class Client;
class Channel;

class server
{
	private:
		std::unordered_map<int, std::pair<std::string, bool> > 		client_data;
		static int 													_port;
		static std::string 											_pass;
		std::map<int, Client>										_map;//fd, client

		std::map<std::string, Channel>								_channels;//channel name, channel
		
	public:
		server(/* args */);
		server(int port, std::string pass);
		//server & operator=(const );

		/**********  server methodes *********/

		std::string		get_pass();
		int				get_port();
		bool			get_authentication();
		void			set_pass(std::string pass);
		void			set_port(int port);
		void			set_authentication(bool);
		void        	run();


		struct addrinfo *get_address();
		int             request_handler(int i, fd_set *master);
		void   			parse_request(char *read, int fd);
		int 			create_socket(struct addrinfo *bind_adress);
		bool			bind_and_listen(int socket_listen, struct addrinfo *bind_adress);
		int				accept_connection(int socket_listen, fd_set *master, int *max_socket);

		/**********  Commands  *********/

		std::string 	pass_response(std::vector<std::string> split, Client &client);
		std::string 	nick_response(std::vector<std::string> split, Client &client);
		std::string 	user_response(std::vector<std::string> split, Client &client);
		std::string 	join_response(std::vector<std::string> split, Client &client);
		std::string 	part_response(std::vector<std::string> tokens, Client &client);

		/********** channels methodes *************/

		void	remove_channel(std::string name);

		/**********  destructor *********/
		~server();
};

bool is_valid_arg(int ac, char **av);

/***** SERVER FUNCTIONS ****/
int 	create_socket(struct addrinfo *bind_adress);
bool    bind_and_listen(int socket_listen, struct addrinfo *bind_adress);
int 	accept_connection(int socket_listen, fd_set *master, int *max_socket);
std::vector<std::string> ft_split(std::string str, char sep);
std::string ft_message(std::string a, std::string b, std::string c, int flg);


# endif