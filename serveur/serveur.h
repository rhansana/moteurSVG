//
// Created by hansana on 24/02/2020.
//

#ifndef CHEVALIER_HANSANA_SAJOT_ROBIN_SERVEUR_H
#define CHEVALIER_HANSANA_SAJOT_ROBIN_SERVEUR_H

#include <string>
#include <netinet/in.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>
#include <vector>
#include <array>

#include "gtk_window.h"

#include "../lib/cbor/cbor11.h"
#include "../lib/tinyxml2/tinyxml2.h"

#define PORT 6789
#define MAXLINE 1024

class Serveur {

private:
    int socketfd;
    sockaddr_in servaddr;
    sockaddr_in cliaddr;
    char* svg;
    Gtk_window *gtk_w;

public:
    Serveur(char*,Gtk_window);


    void loopServ();

    void newValueTarget(cbor::map, std::map<const char*,const char*>);
    void registerNewValue(std::map<const char*,const char*>);
    std::map<const char*,const char*> getFileTarget();

};
#endif //CHEVALIER_HANSANA_SAJOT_ROBIN_SERVEUR_H
