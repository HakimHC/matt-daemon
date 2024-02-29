#include "Server.hpp"
#include "TintinReporter.hpp"
#include "utils.hpp"

#include <exception>
#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>

#include <string.h>

Server::Server()
    : _port(4242)
{
    TintinReporter::info("Creating server.");
    this->_sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_sfd < 0)
        throw std::runtime_error("fatal: socket() failed.");
    
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));

    addr.sin_port = htons(this->_port);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(this->_sfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        TintinReporter::error("fatal: strerror: " + std::string(strerror(errno)));
        throw std::runtime_error("fatal: bind() failed.");
    }
    if (listen(this->_sfd, MAX_CLIENTS) < 0)
        throw std::runtime_error("fatal: listen() failed.");
    TintinReporter::info("Server created.");
}

Server::~Server() {}

Server::Server(const Server& other)
    : _port(4242)
{
    *this = other;
}

Server& Server::operator=(const Server& rhs) {
    if (this != &rhs) {
        this->_sfd = rhs._sfd;
    }
    return *this;
}

void Server::run() {
    FD_ZERO(&this->_fds);
    FD_SET(this->_sfd, &this->_fds);

    char buf[MAX_CLIENT_BODY_SIZE + 1];

    this->_nfds = this->_sfd + 1;

    bool end = false;

    while (!end) {
        this->_readFds = this->_fds;

        if (select(this->_nfds, &this->_readFds, NULL, NULL, NULL) < 0)
            throw std::runtime_error("select() failed.");

        for (int curr = 0; curr < this->_nfds; curr++) {
            if (FD_ISSET(curr, &this->_readFds)) {
                if (curr == this->_sfd) { this->_acceptClient(); break; }

                bzero(buf, sizeof(buf));
                int r = recv(curr, buf, MAX_CLIENT_BODY_SIZE, 0);

                if (r <= 0) {
                    TintinReporter::info("Client disconnected from the server...");
                    this->_eraseClient(curr);
                    TintinReporter::debug(
                        "Current client size: " + utils::itoa(this->_clients.size())
                    );
                    break;
                }

                std::string trimmedMessage = utils::trim(buf);

                if (trimmedMessage == "quit") {
                    TintinReporter::info("Request quit.");
                    this->_stopServer();
                    end = true;
                    break;
                }

                TintinReporter::info("User input: " + trimmedMessage);
            }
        }
    }
}

void Server::_acceptClient() {
    int cfd = accept(this->_sfd, NULL, NULL);

    if (this->_clients.size() >= MAX_CLIENTS) {
        TintinReporter::warning("Client size already at full capacity.");
        close(cfd);
        return;
    }
    FD_SET(cfd, &this->_fds);
    TintinReporter::debug("Accepting client...");
    this->_clients.push_back(cfd);

    this->_nfds = (this->_sfd > cfd) ? this->_sfd + 1 : cfd + 1;
}

void Server::_eraseClient(const int& fd) {
    this->_clients.erase(
        std::find(this->_clients.begin(), this->_clients.end(), fd)
    );
    FD_CLR(fd, &this->_fds);
}

void Server::_stopServer() {
    for (
        std::vector<int>::iterator it = this->_clients.begin();
        it != this->_clients.end();
        it++
    ) this->_eraseClient(*it);

    close(this->_sfd);
}
