#include "Scene.h"
Scene::Scene() {
	mReinit = true;
	m_SceneName = "Default Scene Name";
}

Scene::~Scene() {
}

void Scene::init() {
	mReinit = false;
}

void Scene::Reinit() {
	mReinit = true;
}
