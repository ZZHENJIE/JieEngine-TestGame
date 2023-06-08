#ifndef PLAYER_H
#define PLAYER_H

#include "JieEngine/Animal.h"
#include "JieEngine/Mixer.h"

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
            this->Score = new Mixer("./Resource/Score.mp3",4);
            this->MoveSpeed = 15;
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
            if(strcmp(component->GetClass(),"Glod") == 0){
                component->Position.y += WINDOW_H;
                component->ObjectAnimation->Stop();
                this->Score->Play();
            }
        }

        void Free(){
            this->ObjectAnimation->Free();
            this->Score->Free();
        }
    private:
        Mixer * Score;
};

#endif