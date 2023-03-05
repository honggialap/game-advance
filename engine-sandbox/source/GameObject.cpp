#include "GameObject.h"

#include "Game.h"
#include "Scene.h"

GameObject::GameObject(Game* pGame, Scene* pScene)
	: game(pGame), scene(pScene) {
}

GameObject::~GameObject() {
}
