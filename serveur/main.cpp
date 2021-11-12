#include "gtk_window.h"
#include "serveur.h"
#include <thread>

int main(int argc, char *argv[]){
    Gtk_window w(500, 500,argv[1]);
    w.init(&argc, &argv);
    Serveur s1(argv[1],w);

    std::thread first(w.start);
    std::string in;
    while(true) {
        s1.loopServ();
    }
    first.join();
    return 0;
}