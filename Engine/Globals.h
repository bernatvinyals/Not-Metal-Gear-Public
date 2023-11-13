#pragma once
#include <math.h>
#include <SDL_rect.h>
#include <stdio.h>
#define GAME_NAME "Totally Not Metal Gear"
#define SCREEN_WIDTH 256  
#define SCREEN_HEIGHT 212 
#define GAMEPLAY_SCREEN_WIDTH 256 
#define GAMEPLAY_SCREEN_HEIGHT 192
#define SCREEN_WIDTH_WINDOW 768 
#define SCREEN_HEIGHT_WINDOW 636
#define TILEMAP_WIDTH 32           // TODO: change this to the amount of original MSX map size
#define TILEMAP_HEIGHT 24          // TODO: change this to the amount of original MSX map size

#define ITEMS_GX_PATH "./assets/img/persistent/persistentweapons&Items.png"
#define BULLET_GX_PATH "./assets/img/persistent/bullet.png"

#define DEBUG_STRING "...////+++\\\\..." 

#define PRINT_TRANSFORM printf("\nTransform: X: %d - Y: %d -- W: %d H: %d\n",m_rect.x,m_rect.y,m_rect.w,m_rect.h);
#define PRINT_PLAYER_CENTER printf("\nTransform: X: %d - Y: %d -- W: %d H: %d\n", GetCenterPointInWorld()->x, GetCenterPointInWorld()->y,m_rect.w,m_rect.h);
#define PRINT_TRANSFORM_IN_WORLD printf("\nTransform: X: %d - Y: %d -- W: %d H: %d\n",m_worldRect.x, m_worldRect.y, m_worldRect.w, m_worldRect.h);
#define PRINT_TRANSFORM_(transform) printf("\nTransform: X: %d - Y: %d -- W: %d H: %d\n",transform.x, transform.y, transform.w, transform.h);



typedef float FLOAT;
typedef unsigned char BYTE;
#define TRUE true;
#define FALSE false;
typedef signed int INT;
typedef signed __int32 INT_32;
typedef signed __int16 INT_16;
typedef signed __int8 INT_8;
typedef unsigned int UINT;
typedef unsigned __int32 UINT_32;
typedef unsigned __int16 UINT_16;
typedef unsigned __int8 UINT_8;



namespace LAZY {
	struct TRANSFORM
	{
		int x;
		int y;
		int w;
		int h;
		FLOAT angle;
		static TRANSFORM Zero() {
			TRANSFORM Ret = { 0,0,0,0,0 };
			return Ret;
		}
		static bool Contains(TRANSFORM t1, TRANSFORM t2) {
				///printf("Transform 1: %d %d %d %d\n", t1.x, t1.y, t1.w, t1.h);
				///printf("Transform 2: %d %d %d %d\n", t2.x, t2.y, t2.w, t2.h);

			if ((t2.w<t1.w)&&(t2.x>t1.x)&&(t2.y>t1.y)&&(t2.h<t1.h))
			{
				return true;
			}
			return false;
		}
		SDL_Rect ToSDL() {
			SDL_Rect tempRect = { this->x, this->y,  this->w, this->h };
			return tempRect;
		}
		static TRANSFORM Convert(SDL_Rect rect) {
			return { rect.x,rect.y,rect.w,rect.h,0 };
		}
	};
	enum DIRECTIONS
	{
		UP,DOWN,LEFT,RIGHT,CENTER,_LAST
	};
	struct COLOR {
		UINT_8 r;
		UINT_8 g;
		UINT_8 b;
	};
	struct POINT
	{
		int x;
		int y;
		static bool Equals(POINT& x, POINT& y) {return ((x.x == y.x) && (x.y == y.y));}
		static float Distance(POINT& x, POINT& y) { return sqrtf((float)((x.x-y.x)* (x.x - y.x) + (x.y - y.y) * (x.y - y.y)));}
		static POINT Difference(POINT& x, POINT& y) { return { (x.x - y.x),(x.y - y.y) }; }
	};
}
inline float lerp(float t, float a, float b) {
	return a + t * (b - a);
};

inline float map(float val, float ogMin, float ogMax, float newMin, float newMax) {
	float prop = (val - ogMin) / (ogMax - ogMin);
	return lerp(prop, newMin, newMax);
};
