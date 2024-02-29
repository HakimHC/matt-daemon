#ifndef SERVER_HPP
#define SERVER_HPP

#define MAX_CLIENTS 3
#define MAX_CLIENT_BODY_SIZE 2048

#include <map>
#include <vector>
#include <algorithm>
#include <string>

#include <sys/select.h>

class Server {
    public:
        Server();
        ~Server();
        Server(const Server&);
        Server& operator=(const Server&);

        void run();

    private:
        int _sfd;
        const unsigned short _port;

        std::vector<int>            _clients;
        int                         _nfds;
        fd_set                      _fds;
        fd_set                      _readFds;

        static bool                 _end;

        void                        _acceptClient();
        void                        _eraseClient(const int&);
        void                        _stopServer();


};

#endif //SERVER_HPP