#pragma once
#include "Actor.h"
#include "UIText.h"
#include <vector>
#include <string>
class ANotification :
    public Actor
{

    std::vector<std::string*> queue_Notifications;
    UIText* pickup;
    UIText* show;
public:
    ANotification();
    ~ANotification();
    
    void StartPlay();

    void Render();

    void AddNotification(const char* _str) {
        queue_Notifications.push_back(new std::string(_str));
        show = new UIText(_str, "./assets/fonts/Mulish-Regular.ttf", 14, { 25,24,0,0 }, { 255,255,255 });
    }

};

