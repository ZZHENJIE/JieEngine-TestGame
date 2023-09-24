#pragma once

#include "JieEngine/JE.h"

using namespace JieEngine;

class Barrier;

class Gold : public JEEntity{
public:
    Gold(JETransform * Transform){
        JETransform * TransformData = &this->GetComponent<JETransform>();
        TransformData->Position.X = Transform->Position.X;
        TransformData->Position.Y = Transform->Position.Y - 150;
        BindTransform  = Transform;
        map<string,JEAnimationImage> Image;
        if(JECreateAnimationImage("Gold",6,Image["None"]) == SUCCEED){
            Image["None"].PlaySpeed = 30;
            this->AddComponent<JEAnimation>({
                Image,"None",true
            });
        }
        auto Body = JECreateCircleBody(40,b2_staticBody,this);
        Body->SetTitle("Gold");
        this->AddComponent<JEPhysics>({
            Body
        });
    }
    ~Gold(){

    }
private:
    void Update(){
        auto Component = this->GetComponent<JEPhysics>();
        Component.Body->SetTransform(JEVec2(BindTransform->Position.X,BindTransform->Position.Y - 150),0.0f);
        auto Transform = &this->GetComponent<JETransform>();
        Transform->Position.X = BindTransform->Position.X;
        Transform->Position.Y = BindTransform->Position.Y - 150;
    }
    void Event(SDL_Event Event){

    }
private:
    friend Barrier;
    JETransform * BindTransform;
};

class Barrier : public JEEntity{
public:
    Barrier(JETransform TransformData){
        JETransform * Transform = &this->GetComponent<JETransform>();
        Transform->Position = {TransformData.Position.X,TransformData.Position.Y};
        JEImage Image;
        if(JECreateImage("Barrier",Image) == SUCCEED){
            this->AddComponent<JEImage>(Image);
        }
        auto Body = JECreateRectBody({100.0f,200.0f},b2_staticBody,this,{0.1f,0.1f,0.3f});
        this->AddComponent<JEPhysics>({Body});
        GoLd = new Gold(Transform);
        GoLdID = GoLd->GetID();
    }
    ~Barrier(){
        delete GoLd;
    }
private:
    void Update(){
        JEAnimationSystem(GoLdID);
        JETransform * Transform = &this->GetComponent<JETransform>();
        if(Transform->Position.X <= 55){
            Transform->Position.X = 700;
            Transform->Position.Y = (rand() % (500 - 210));
            if(Transform->Position.Y <= 200){
                Transform->Position.Y += 180;
            }
            GoLd->GetComponent<JEAnimation>().Enabled = true;
            GoLd->GetComponent<JEPhysics>().Body->SetEnabled(true);
        }
        Transform->Position.X -= 0.2f;
        this->GetComponent<JEPhysics>().Body->SetTransform(JEVec2(Transform->Position.X,Transform->Position.Y),0.0f);
        GoLd->Update();
    }
    void Event(SDL_Event Event){

    }
private:
    JEUnInt GoLdID;
    Gold * GoLd;
};