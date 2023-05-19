#pragma once
#ifndef __CLIENT_TURRET_H__
#define __CLIENT_TURRET_H__

#include "game_object.h"

class Turret : public GameObject {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

public:
	static Turret* Create(
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
typedef Turret* pTurret;

#endif // !__CLIENT_TURRET_H__
