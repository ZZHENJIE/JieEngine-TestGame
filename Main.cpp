#include "./JieEngine/Window.h"
#include "MainMapBackground.h"
#include "MainMapStruct.h"

int main(int argc, char * argv[]){

    Window * MWindow = new Window("JieEngine测试","./Resource/Logo.bmp");

    MapBackground * MainMapbackground = new MainMapBackground(MWindow->GetWindowSurface());

    MapStruct * MainMapstruct = new MainMapStruct(MWindow->GetWindowSurface());

    Map * One = new Map(MainMapbackground,MainMapstruct,MWindow->GetWindowSurface());

    MWindow->SetMap(One);

    MWindow->ListenEvent();

    return 0;
}