#pragma once
#ifdef _WIN64
#include "SDL.h"
#include "SDL_image.h"
#endif //Windows Includes
#ifdef linux
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#endif //Linux includes
#include "Globals.h"


//Future:
//With these enums Create Actor can automatically get centred or be scaled
typedef enum
{
	ACTOR_SCALABLE = 0x00000001,
	ACTOR_CENTER = 0x00000002,
	ACTOR_UNCENTRED = 0x00000003
} ACTOR_INIT_FLAGS;

class Actor
{
private:
	bool hasImage;
	
protected:
	bool m_debug;
	SDL_Rect m_rect; //In Camera
	LAZY::TRANSFORM m_worldRect; //In world
	Sint32 m_image;
	double m_angle;
	bool canBeRendered;
public:
	Actor();
	~Actor();


	int CreateActor(int p_x, int p_y, const char* file, bool isUI = false,bool crateGraphic = false, int w_x=1, int w_y=1, Uint8 r = 255, Uint8 g= 255, Uint8 b= 255);
	int CreateActor(LAZY::TRANSFORM transform, const char* file, bool crateGraphic = false, LAZY::COLOR rgb = {255,255,255});

	int CreateActorWithImage(const char* file);
	int CreateCentredActorScale(int w, int h); //Do not use yet


	SDL_Rect* GetRect() { return &m_rect; }
	LAZY::TRANSFORM* GetWorldRect() { return &m_worldRect; }
	virtual int GetLookingDirection();
	void ChangeTransform(int p_x, int p_y, int p_sx, int p_sy);
	void CenterActor();
	void SetAlpha(int alpha);
	void SetImage(const char* file);



	void StartPlay();
	virtual void Update();
	virtual void Render();


	void SetX(int p_x) { 
		m_worldRect.x = p_x; 
	}
	void SetY(int p_y) { 
		m_worldRect.y = p_y;
	}
	void SetScreenX(int p_x) {
		m_rect.x = p_x;
	}
	void SetScreenY(int p_y) {
		m_rect.y = p_y;
	}
	void SetX(float p_x) { m_worldRect.x = (int)p_x; }
	void SetY(float p_y) { m_worldRect.y = (int)p_y; }

	int GetX() { return m_worldRect.x; }
	int GetY() { return m_worldRect.y; }
	
	void SetCanBeRendered(bool value) { canBeRendered = value; }

	void UpdateRelToCam();

	int CheckIfOutOfBounds();
};

