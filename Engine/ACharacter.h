#pragma once
#include "Actor.h"
#include "UIProggressBar.h"
#include "../AItem.h"
#include <vector>
#include "ANotification.h"
#include "UIProggressBar.h"
enum CharaterState
{
    IDLE,
    CUTSCENE,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    STAIRS,
    ATTACK,
    NOTATTACK
};
class ACharacter : public Actor
{
    float m_velocity;
    CharaterState m_state;
    CharaterState m_subState;
    int m_frame;
    int m_frameH;
    int m_animtionRow;
    int m_a_animationTimer;
    int m_a_animationTimerStairs;
    bool m_weaponInHand;
    int m_maxFrame;
    int m_hp;
    UIProggressBar* UIhpVar;
    Actor* UIBg;
    bool alreadyPunching;
    bool m_applyMovement;
    //!Changes frame based on State
    void ChangeAnimationFrame();


public:

    ACharacter();
    ~ACharacter();

    //SetSpriteSize for render
    void SetSpriteSize(int w, int h);

    //! This sets velocity of the object
    /*!
        \param Velocity to set
    */
    void SetVelocity(float pVel) { m_velocity = pVel; };
    float GetVelocity() { return m_velocity; }
    void Init();

    virtual void Update() override;

    void CheckColisionWithWorld(int* directions);

    int GetSpriteWidth() { return m_rect.w; };
    int GetSpriteHeight() { return m_rect.h; };

    //! Retruns the center point position in world
    LAZY::TRANSFORM* GetCenterPointInWorld() {
        return new LAZY::TRANSFORM{
            (m_worldRect.w/2) + m_worldRect.x,
            (m_worldRect.h / 2) + m_worldRect.y
        };
    }

    //! Return current player state
    CharaterState* GetPlayerState() { return &m_state; }

    //! Custom render since it's a sprite sheet
    virtual void Render() override;
    virtual void RenderUI();
    //! Makes the object not go out of the screen
    /*!
        \return Returns 0 if the object is inside the screen and returns 1 if object was outside
    */
    int CheckOuterColison();

    //0 = DOWN 1=LEFT 2=UP 3=RIGHT
    int GetLookingDirection() override {
        return m_animtionRow;
    }
    void SetHP(int _val) {
        m_hp = _val;
    }
    void ReduceHP(int _dmg)
    {
        m_hp -= _dmg;
        printf("HP: %d \n", m_hp);
        UIhpVar->ChangePercentage(m_hp, 100);
    }

};
