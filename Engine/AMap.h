#pragma once
#include "Actor.h"
#include "Globals.h"
#include "../libraries/TinyXML/tinyxml2.h"
#include <vector>
#include "Camera.h"

class AMap :
    public Actor
{

    std::vector<std::vector<int>> map;
    std::vector<std::vector<int>> colision;

    int TW;
    int TH; 
    int WTW;
    int WTH;
    int WX; //Coords: Mon
    int WY; //Coords: Mon
    int tileSetSpacing;
    int tileID;

    SDL_Rect rectS, rectT;
    tinyxml2::XMLElement* root;

    int tilesetSelectedColumn;
    int tilesetSelectedRow;

    int tilesetAmountColumns;

    Camera* cameraRef;


    //Map Elements
    std::vector <Actor*> listOfObjectsInMap;
public:

    AMap(const char* tilemap, int tileset, Camera* _cam = nullptr);
    ~AMap();

    void Update();
    void Render();
    std::vector<std::vector<int>>* GetMapArray() { return &map; }
    void AddActor(Actor* actor) { listOfObjectsInMap.push_back(actor); }

    void CamaraStepDown() {
        if (cameraRef != nullptr)
        {
            cameraRef->SetY(cameraRef->GetY() + GAMEPLAY_SCREEN_HEIGHT);
        }
    };
    void CamaraStepUp() {
        if (cameraRef != nullptr)
        {
            cameraRef->SetY(cameraRef->GetY() - GAMEPLAY_SCREEN_HEIGHT);
        }
    };
    void CamaraStepLeft() { 
        if (cameraRef != nullptr)
        {
            cameraRef->SetX(cameraRef->GetX() - GAMEPLAY_SCREEN_WIDTH);
        }
    };
    void CamaraStepRight() {
        if (cameraRef != nullptr)
        {
            cameraRef->SetX(cameraRef->GetX() + GAMEPLAY_SCREEN_WIDTH);
        }
    };
    Camera* GetCamera() {
        return cameraRef;
    }

    //0 = MAP 1=COLISION
    int GetTileFromMap(int _map, int _x, int _y);
};

