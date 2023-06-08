#ifndef MAPSTRUCT_H
#define MAPSTRUCT_H

#include "JieEngine.h"
#include "Still.h"
#include "Animal.h"

class MapStruct : public JieEngine{
    public:
        /*
            获取类名
        */
        virtual const char * GetClass(){
            return "MapStruct";
        }
        /*
            每帧更新函数
        */
        virtual void Update() = 0;
        /*
            接收事件 除了退出事件 其它事件都接收的到
        */
        virtual void WindowEvent(SDL_Event Event) = 0;
    protected:
        Still * MapStillArray;
        short StillCount = 0;
        Animal * MapAiArray;
        short AiCount = 0;
        Animal * PlayerObject;
};

#endif 