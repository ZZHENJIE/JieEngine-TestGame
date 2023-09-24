#include "MainMap.h"

int main(int argc,char * argv[]){

    JEInit();

    Resource.ResourceFile = new JEUnpackData("./Resource.JieEngine");
    
    JEChangeGameMap(new Main());
    
    JEWorld * GameWorld = new JEWorld({600.0f,500.0f},{0.0f,10.0f});

    GameWorld->CreateWindowAndRenderer("JieEngine",600,500);

    GameWorld->SetIcon("Logo");

    GameWorld->Booting();

    JEQuit();

    return 0;
}