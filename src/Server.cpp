#include "Server.hpp"
#include "TintinReporter.hpp"

#include <exception>
#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>

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

    if (bind(this->_sfd, (struct sockaddr*)&addr, 0) < 0)
        throw std::runtime_error("fatal: bind() failed.");
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