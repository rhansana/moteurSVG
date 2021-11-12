
#include "client.h"

Client::Client() {

    // Creating socket file descriptor
    this->socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if ( this->socketfd < 0 ) {
        std::cout << ("socket creation failed") << std::endl;
    }

    memset(&this->servaddr, 0, sizeof(this->servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
}

void Client::sendMsg(const char *msg) {

    sendto(this->socketfd,msg,strlen(msg),
                  MSG_CONFIRM,reinterpret_cast<sockaddr *>(&this->servaddr),
                  sizeof(this->servaddr));
    close(this->socketfd);
}

cbor::map Client::test() {
    std::string x;
    std::string y;
    std::cout << "Entrez la valeur X" << std::endl;
    std::cin >> x;

    while ((std::stoi(x) < 9) | (std::stoi(x) > 99)){
        std::cout << "Entrez une valeur X supérieur à 9 et inférieur à 100" << std::endl;
        std::cin >> x;
    }

    std::cout << "Entrez la valeur Y" << std::endl;
    std::cin >> y;

    while ((std::stoi(y) < 9) | (std::stoi(y) > 99)){
        std::cout << "Entrez une valeur Y supérieur à 9 et inférieur à 100" << std::endl;
        std::cin >> y;
    }

    cbor::map data = cbor::map{
            { "sun_x", x },
            { "sun_y", y }
    };

    return data;
}

void Client::sendData(cbor::map data){

    cbor::binary encoded = cbor::encode(data);
    std::vector<unsigned char> msg = encoded;
    int i = 0;
    char* trueMsg = new char[msg.size()];
    for(auto it = msg.begin(); it != msg.end(); ++it) {
        trueMsg[i]=(*it);
        i++;
    }

    if(sendto(this->socketfd,trueMsg,strlen(trueMsg),
           0,(const sockaddr *)(&this->servaddr),
           sizeof(this->servaddr)) < 0){
        std::cout << "Erreur Message envoyé" << std::endl;
    }else{
        std::cout << "Message bien envoyé" << std::endl;
    }

    close(this->socketfd);
}


