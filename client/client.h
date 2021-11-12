//
// Created by hansana on 24/02/2020.
//

#ifndef CHEVALIER_HANSANA_SAJOT_ROBIN_CLIENT_H
#define CHEVALIER_HANSANA_SAJOT_ROBIN_CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <cstring>
#include <vector>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

#include "../lib/cbor/cbor11.h"

#define PORT 6789
#define MAXLINE 1024
class Client{

private:
    int socketfd;
    sockaddr_in servaddr;

public:
    Client();

    void sendMsg(const char*);
    void sendData(cbor::map);

    cbor::map test();
};
#endif //CHEVALIER_HANSANA_SAJOT_ROBIN_CLIENT_H
