#ifndef CHANNEL_HPP
# define CHANNEL_HPP

class Channel
{
	private:
	std::string _name;//channel name
	std::string _pass;//password
	bool  		_key;//true if channel has a key
	std::map<int, Client> _clients;//fd, client
	public:

		Channel();
		Channel(std::string name, std::string pass)
		Channel( Channel const & src );
		~Channel();

};

#endif 