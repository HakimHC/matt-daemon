#ifndef SERVER_HPP
#define SERVER_HPP

#define MAX_CLIENTS 3

class Server {
    public:
        Server();
        ~Server();
        Server(const Server&);
        Server& operator=(const Server&);
    private:
        int _sfd;
        const unsigned short _port;
};

#endif //SERVER_HPP