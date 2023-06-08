#ifndef PLAYER_H
#define PLAYER_H

#include "JieEngine/Animal.h"

class Player : public Animal{
    public:
        /*
            获取类名
        */
        virtual const char * GetClass(){
            return "Player";
        }

        Player(const char * FileUrl,short ImageInciseNumber,short PlaySpeed,SDL_Point Position,SDL_Surface * WindowSurface){
            this->SetData(FileUrl,ImageInciseNumber,PlaySpeed,Position,WindowSurface);
            this->MoveSpeed = 15;
        }

        Player(const char * FileUrl,SDL_Point Position,SDL_Surface * WindowSurface){
            this->SetData(FileUrl,Position,WindowSurface);
        }
    
        void Jump(){
            if(this->Position.y - MoveSpeed > 0){
                this->Position.y -= MoveSpeed;
            }
        }

        void MoveRight(){
            if(this->Position.x + MoveSpeed < WINDOW_W - this->Size.x){
                this->Position.x += MoveSpeed;
            }
        }

        void MoveLeft(){
            this->Position.x -= MoveSpeed;
        }

        void MoveDown(){
            this->Position.y += MoveSpeed;
        }

        void Update(){
            this->ObjectAnimation->Update();
            this->Position.y ++;
        }

        void Collide(Component * component,SDL_Rect CollideRect,short CollidePosition){

        }

        void Free(){
            this->ObjectAnimation->Free();
        }
};

#endif