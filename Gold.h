#ifndef GOLD_H
#define GOLD_H

#include "include/Still.h"

class Gold : public Still{
    public:
        /*
            获取类名
        */
        virtual const char * GetClass(){
            return "Glod";
        }

        /*
            构造函数 参数为 动画素材路径 动画分割数量 播放速度(数值越大越慢) 显示位置 WindowSurface
        */
        void SetData(const char * FileUrl,short ImageInciseNumber,short PlaySpeed,SDL_Point Position,int W,SDL_Surface * WindowSurface){
            this->ObjectAnimation = new Animation(FileUrl,ImageInciseNumber,PlaySpeed,&this->Position,WindowSurface);
            this->Size = ObjectAnimation->GetComponentSize();
            this->Position.x = Position.x + (W/2 - this->Size.x/2);
            this->Position.y = Position.y - Size.y;
            this->WindowSurface = WindowSurface;
        }

        void SetPos(SDL_Point Position,int W){
            this->Position.x = Position.x + (W/2 - this->Size.x/2);
            this->Position.y = Position.y - Size.y;
        }
        
        void Update(){
            this->ObjectAnimation->Update();

        }

        void Free(){
            ObjectAnimation->Free();
            
        }
};

#endif