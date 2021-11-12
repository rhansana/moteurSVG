
// Server side implementation of UDP client-server model

#include "serveur.h"

Serveur::Serveur(char* svg,Gtk_window gtk) {

    // Creating socket file descriptor
    this->socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if ( this->socketfd < 0 ) {
        std::cout << ("socket creation failed") <<std::endl;
    }

    memset(&this->servaddr, 0, sizeof(this->servaddr));
    memset(&this->cliaddr, 0, sizeof(this->servaddr));

    // Filling server information
    this->servaddr.sin_family    = AF_INET; // IPV4
    this->servaddr.sin_addr.s_addr = INADDR_ANY; // écoutes sur les interfaces locaux
    this->servaddr.sin_port = htons(PORT); //on traduit le port

    int msgBind = bind(this->socketfd, (const struct sockaddr *)&this->servaddr,
            sizeof(this->servaddr));
    if ( msgBind < 0 )
    {
        std::cout << ("bind failed") << std::endl;
    }

    this->svg = svg;

    this->gtk_w = &gtk;

}

void Serveur::loopServ(){

    while (true) {

        ssize_t msg;
        char buffer[MAXLINE];
        socklen_t len = sizeof(this->cliaddr);

        std::cout<<"j'écoute : " << std::endl;

        msg = recvfrom(this->socketfd,buffer, MAXLINE,
                0, reinterpret_cast<sockaddr *> (&cliaddr),&len);

        if (msg <= 0) {
            std::cout << ("Problème de reception de données")<< std::endl;
        }else{

            std::string message;

            for(int i =0; i<msg; i++){
                message = message + buffer[i];
            }

            std::vector<unsigned char> encodedBuffer(message.begin(),message.end());

            cbor item = cbor::decode(encodedBuffer);

            if(item.is_map()){
                cbor::map laMap = item.to_map();
                newValueTarget(laMap,this->getFileTarget());

            }else{
                std::cout << "C'est pas une map" << std::endl;
            }
        }
    }
}

std::map<const char*,const char*> Serveur::getFileTarget() {
    tinyxml2::XMLDocument svg_data;
    svg_data.LoadFile(this->svg); // on charge "toto.svg"

    std::map<const char *,const char*> theKey;

    tinyxml2::XMLElement *root = svg_data.FirstChildElement("svg"); // on initialise dans la balise svg
    std::vector < tinyxml2::XMLElement * > lifo;
    lifo.push_back(root); // pile pour le parcours en profondeur

    while (!lifo.empty()) {
        tinyxml2::XMLElement *son = lifo.back();
        lifo.pop_back();
        if (std::string(son->Value()).compare("driven") == 0) { // Si on est dans un driven on récup le by et target
            theKey.insert(std::pair<const char*,const char*>(son->Attribute("by"),son->Attribute("target")));
        }
        tinyxml2::XMLElement *bro = son->NextSiblingElement(); 
        if (bro != NULL) {
            lifo.push_back(bro);
        }
        tinyxml2::XMLElement *grandson = son->FirstChildElement();
        if (grandson != NULL) {
            lifo.push_back(grandson);
        }
    }

    return theKey;
}

// Créer une map de type : "target : value"
void Serveur::newValueTarget(cbor::map mapValue,
        std::map<const char*,const char*> mapTarget) {

    int size = (int) mapTarget.size();

    std::vector<const char*> value; // vecteur de valeur qu'on à récup de la map du client
    std::vector<const char*> target; // vecteur du nom des attributs qu'on récup avec getFileTarget
    std::map<const char*,const char*> newMap; // Map en question de type "target : value"

    for(auto it1 = mapValue.begin(); it1 != mapValue.end(); ++it1) {
        std::string val = it1->second.to_string();
        value.push_back(val.c_str());
    }

    for(auto it2 = mapTarget.begin(); it2 != mapTarget.end(); ++it2) {
        target.push_back(it2->second);
    }

    for(int i = 0 ; i<size;i++) {
        std::cout << target.back() << " : " << value[i] << std::endl;
        newMap.insert(std::pair<const char*, const char*>(target.back(), value.back() )); // création de la nouvelle map
        target.pop_back();
        value.pop_back();
    }

    registerNewValue(newMap);
}

void Serveur::registerNewValue(std::map<const char *, const char*> map) {
    tinyxml2::XMLDocument svg_data;
    svg_data.LoadFile(this->svg); // on charge "toto.svg"

    tinyxml2::XMLElement *root = svg_data.FirstChildElement("svg"); // on initialise dans la balise svg
    std::vector < tinyxml2::XMLElement * > lifo;
    lifo.push_back(root);

    while (!lifo.empty()) {
        tinyxml2::XMLElement *son = lifo.back();
        lifo.pop_back();
        if (std::string(son->Value()).compare("circle") == 0) { // on cherche la balise circle pour changer ses attributs
            for(auto it = map.begin(); it != map.end(); ++it) {
                std::string val = std::string(it->first);
                std::string str = val.substr(0, 2);
                son->SetAttribute(str.c_str(), it->second);
                tinyxml2::XMLPrinter prt;
                svg_data.Print(&prt);
                RsvgHandle* svg_handle = rsvg_handle_new_from_data ((const unsigned char*) prt.CStr(),
                                                        prt.CStrSize()-1, NULL);
                this->gtk_w->setHandler(svg_handle);
                gtk_widget_queue_draw (this->gtk_w->getWidget());
                std::cout << "zizir" << std::endl;
            }
        }
        tinyxml2::XMLElement *bro = son->NextSiblingElement();
        if (bro != NULL) {
            lifo.push_back(bro);
        }
        tinyxml2::XMLElement *grandson = son->FirstChildElement();
        if (grandson != NULL) {
            lifo.push_back(grandson);
        }
    }
    svg_data.SaveFile("toto.svg");
}