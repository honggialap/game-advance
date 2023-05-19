#pragma once
#ifndef __CLIENT_CREEP_BULLET_H__
#define __CLIENT_CREEP_BULLET_H__

#include "game_object.h"

class CreepBullet : public GameObject {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	uint32_t team = 0;

public:
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

#endif // !__CLIENT_CREEP_BULLET_H__
