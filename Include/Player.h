#pragma once

#include "JieEngine/JE.h"

using namespace JieEngine;

class Player : public JEEntity{
public:
    Player(){
        JETransform * TransformData = &this->GetComponent<JETransform>();
        TransformData->Position = {200.0f,100.0f};
        map<string,JEAnimationImage> Image;
        if(JECreateAnimationImage("Player",4,Image["None"]) == SUCCEED){
            Image["None"].PlaySpeed = 30;
            this->AddComponent<JEAnimation>({
                Image,"None",true
            });
        }
        Body = JECreateRectBody(Image["None"].Size,b2_dynamicBody,this,{0.3f,0.3f,0.0f});
        Body->SetTitle("Player");
        Body->SetCollideFunction([](b2Body *MainBody, b2Body *DeputyBody){
            if(strcmp(DeputyBody->GetTitle(),"WorldBorder_Left") == 0){
                Player * Temp = (Player*)MainBody->GetEntity();
                Mix_PlayChannel(Temp->Audio["Die"].Channel,Temp->Audio["Die"].Sound,0);
                SDL_Delay(2000);
                Resource.Run = false;
            }else if(strcmp(DeputyBody->GetTitle(),"Gold") == 0){
                Player * Temp = (Player*)MainBody->GetEntity();
                Mix_PlayChannel(Temp->Audio["Score"].Channel,Temp->Audio["Score"].Sound,0);
                DeputyBody->SetEnabled(false);
                JEEntity * Gold = (JEEntity*)DeputyBody->GetEntity();
                JEComponentManage::GetComponentData<JEAnimation>(Gold->GetID()).Enabled = false;
            }
        });
        this->AddComponent<JEPhysics>({Body});
        JECreateAudio("Move",Audio["Move"]);
        JECreateAudio("Die",Audio["Die"]);
        JECreateAudio("Score",Audio["Score"]);
    }
    ~Player(){
        for(auto I : Audio){
            JEDestroyAudio(I.second);
        }
    }
    map<string,JEAudio> Audio;
private:
    void Update(){
        auto Transform = Body->GetTransform().p;
        Transform.y *= -1;
        Body->SetTransform(Transform,0.0f);
    }
    void Event(SDL_Event Event){
        if(Event.key.type == SDL_KEYDOWN){
            switch(Event.key.keysym.sym){
                case SDLK_w:{
                    JEBodyApplyLinearImpulse(Body,{0.0f,-2000.0f});
                    Mix_PlayChannel(Audio["Move"].Channel,Audio["Move"].Sound,0);
                    break;
                }
                case SDLK_a:{
                    JEBodyApplyLinearImpulse(Body,{-2000.0f,0.0f});
                    Mix_PlayChannel(Audio["Move"].Channel,Audio["Move"].Sound,0);
                    break;
                }
                case SDLK_s:{
                    JEBodyApplyLinearImpulse(Body,{0.0f,2000.0f});
                    Mix_PlayChannel(Audio["Move"].Channel,Audio["Move"].Sound,0);
                    break;
                }
                case SDLK_d:{
                    JEBodyApplyLinearImpulse(Body,{2000.0f,0.0f});
                    Mix_PlayChannel(Audio["Move"].Channel,Audio["Move"].Sound,0);
                    break;
                }
            }
        }
    }
private:
    b2Body * Body;
};