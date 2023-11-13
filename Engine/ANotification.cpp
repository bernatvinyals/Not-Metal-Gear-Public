#include "ANotification.h"
#include "../SceneGame.h"
#include "Input.h"
ANotification::ANotification()
{
	queue_Notifications = std::vector<std::string*>();

}

ANotification::~ANotification()
{
}

void ANotification::StartPlay()
{
	pickup = new UIText("Picked Up", "./assets/fonts/Mulish-Regular.ttf", 14, { 25,10,0,0 }, { 255,255,255 });
}

void ANotification::Render()
{
	std::string* tmp = nullptr;
	if (queue_Notifications.size()>0)
	{
		tmp = queue_Notifications.at(0);
	}
	if (tmp != nullptr)
	{
		//Show ui with the string
		pickup->Render();  //This is not showing up
		show->Render();
		SceneGame::gameResume = false;
		if (Input::getInstance()->keyboard.KB_SPACE)
		{
			SceneGame::gameResume = true;
			show->Flush();
			delete show;
			delete tmp;
			queue_Notifications.clear();
		}

	}
}
