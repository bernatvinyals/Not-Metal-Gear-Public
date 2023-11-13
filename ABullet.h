#pragma once
#include "Engine/Actor.h"

class ABullet :
    public Actor
{
    int direction;
    int velocity;
    int dmg;
    bool requestDelete;
    bool isFriendly;
    int m_a_animationTimer;
public:
    ABullet(bool _isfriendly, LAZY::TRANSFORM _transform, int _proj_direction, int _speed, int _dmg);
    ~ABullet();
    void Update();
    void Render();
};

