#ifndef BARRIER_H
#define BARRIER_H

#include "include/Still.h"
#include "Gold.h"

class Barrier : public Still{
    public:
        /*
            获取类名
        */
        virtual const char * GetClass(){
            return "Barrier";
        }
        /*
            构造函数 参数为 图片素材路径 显示位置 WindowSurface
        */
        void SetData(const char * FileUrl,SDL_Point Position,SDL_Surface * WindowSurface){
            this->ObjectAnimation = new Animation(FileUrl,&this->Position,WindowSurface);
            this->Size = ObjectAnimation->GetComponentSize();
            this->Position = Position;
            this->WindowSurface = WindowSurface;
            this->GoLd = new Gold();
            this->GoLd->SetData("./Resource/Gold.png.JieEngine",6,4,Position,Size.x,WindowSurface);
        }
        
        void Update(){
            this->ObjectAnimation->Update();
            this->GoLd->Update();
            if(this->Position.x <= 0){
                this->Position.x = WINDOW_W;
                this->Position.y = rand() % (WINDOW_H - Size.y);
                this->GoLd->SetPos(this->Position,this->Size.x);
                this->GoLd->ObjectAnimation->Play();
            }
            this->Position.x --;
            this->GoLd->Position.x --;
        }

        void Free(){
            ObjectAnimation->Free();
        }

        Gold * GoLd;
};

#endif