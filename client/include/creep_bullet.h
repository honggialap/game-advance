#pragma once
#ifndef __CLIENT__CREEP_BULLET_H__
#define __CLIENT__CREEP_BULLET_H__

#include "client_game_object.h"

class CreepBullet : public ClientGameObject {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	uint32_t team = 0;

public:
	CreepBullet(pGame game, pWorld world);
	~CreepBullet();

	static CreepBullet* Create(
		pGame game, pWorld world,
		std::string name,
		float position_x, float position_y,
		uint32_t layer,
		std::string data_path
	);

	void SetTeam(uint32_t value) { team = value; }
	uint32_t GetTeam() { return team; }

	void Load(std::string data_path) override;
	void Unload() override;

	void HandleInput(uint32_t tick) override;
	void ExecuteCommand(Command* command) override;

	void Update(float elapsed) override;
	void Render(sf::RenderWindow& window) override;

	void OnCollisionEnter(GameObject* other) override;
	void OnCollisionExit(GameObject* other) override;
};
typedef CreepBullet* pCreepBullet;

#endif // !__CLIENT__CREEP_BULLET_H__
