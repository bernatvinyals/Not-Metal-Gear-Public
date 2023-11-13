#pragma once
class Scene
{
public:
	//! Scene Name

	//! Constructor of an empty Scene.
	Scene();

	//! Destructor
	virtual ~Scene();

	//! Initializes the Scene.
	virtual void init();

	//! Function to withdraw anything owned by the class and to call init
	virtual void Reinit();

	//! Handles the drawing of the scene
	virtual void render() = 0;

	//! Handles the updating of the scene
	virtual void update() = 0;

	//! Handles custom unloading of each scene
	virtual void unload(){};

	const char* GetName() { return m_SceneName; }

	void setReInit(bool loaded = true) { mReinit = loaded; };
	bool mustReInit() { return mReinit; };

protected:
	const char* m_SceneName;
	bool mReinit;			/*!<  Reload when returning to scene*/
};