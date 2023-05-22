#pragma once
#ifndef __CLIENT_FACTORY_H__
#define __CLIENT_FACTORY_H__

#include "client_game_object.h"

class Factory : public ClientGameObject {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Factory(Game* game, World* world);
	~Factory();

	static Factory* Create(
		pGame game, pWorld world,
		std::string name,
		float position_x, float position_y,
		uint32_t layer,
		std::string data_path
	);

	void Load(std::string data_path) override;
	void Unload() override;

	void HandleInput(uint32_t tick) override;
	void ExecuteCommand(Command* command) override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnCollisionEnter(GameObject* other) override;
	void OnCollisionExit(GameObject* other) override;
};
typedef Factory* pFactory;

#endif // !__CLIENT_FACTORY_H__