#include "../include/utils.h"
#include <iostream>

namespace zoro::cli {
    
void Health(){
    std::cout << "\nzoro health:\n";
    PrintCmd("server ", "ok");
    PrintCmd("storage ", "ok");
    PrintCmd("wal ", "ok");
    PrintCmd("collections ", "ok");
    PrintCmd("status ", "good", 22, true);
}

void Ping(){
    std::cout<<"PONG"<<std::endl;
}


}