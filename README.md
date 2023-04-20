# ft_irc
Simple IRC Server based on the RFC (mainly 2812) written in C++.

ft_irc does not support server-server communication and is best used with LimeChat (or any client that send packets terminated with \r\n).

# How to Run ?

Do ``` make ```
then run :

``` ./IRC <port> <password> ```

for port you can use: from 6667 up to 6672.<br>
password: you can use password of you choice.<br>


# Handled commands:

``` 
- PASS
- NICK 
- USER
- JOIN
- PART
- TOPIC
- INVITE
- KICK
- MODE
- QUIT
- PRIVMSG
- NOTICE
- WEATHER: for weather bot (bonus part)

```

# 👨‍💻 Ressources
* [What is a Socket?](https://www.tutorialspoint.com/unix_sockets/what_is_socket.htm)
* [Unix Socket - Network Addresses](https://www.tutorialspoint.com/unix_sockets/network_addresses.htm)
* [Unix Socket - Core Functions](https://www.tutorialspoint.com/unix_sockets/socket_core_functions.htm)
* [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/)
* [The UChicago χ-Projects](http://chi.cs.uchicago.edu/chirc/index.html)
* [Internet Relay Chat Protocol](https://datatracker.ietf.org/doc/html/rfc1459)
* [Internet Relay Chat: Architecture](https://datatracker.ietf.org/doc/html/rfc2810)
* [Internet Relay Chat: Channel Management](https://datatracker.ietf.org/doc/html/rfc2811)
* [Internet Relay Chat: Client Protocol](https://datatracker.ietf.org/doc/html/rfc2812)
* [Internet Relay Chat: Server Protocol](https://datatracker.ietf.org/doc/html/rfc2813)
