#ifndef SERVER_HPP
# define SERVER_HPP

#include "headers.hpp"
#include "Client.hpp"

class Client;

class server
{
	private:
		std::unordered_map<int, std::pair<std::string, bool> > client_data;
		static int _port;
		static std::string _pass;
		std::vector<std::string> _nickname;
		std::map<int, Client> _map;

		
	public:
		server(/* args */);
		server(int port, std::string pass);

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
		std::string 	pass_response(std::string buff, Client &client);
		std::string 	nick_response(std::string buff, Client &client);

		/**********  destructor *********/
		~server();
};

bool is_valid_arg(int ac, char **av);

/***** SERVER FUNCTIONS ****/
int request_handler(int i, fd_set *master);
int create_socket(struct addrinfo *bind_adress);
bool    bind_and_listen(int socket_listen, struct addrinfo *bind_adress);
int accept_connection(int socket_listen, fd_set *master, int *max_socket);
//std::string parse_request(char *read);
void    parse_request(char *read, int fd);
std::vector<std::string> ft_split(std::string str, char sep);


# endif