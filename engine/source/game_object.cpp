#include "game_object.h"

namespace Engine {

	GameObject::GameObject(pGame game, pScene scene)
		: game(game), scene(scene) {
	}

	GameObject::~GameObject() {
	}

}