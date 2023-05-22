#pragma once
#ifndef __CLIENT_PLAYER_BULLET_H__
#define __CLIENT_PLAYER_BULLET_H__

#include "client_game_object.h"

class PlayerBullet : public ClientGameObject {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

public:
	PlayerBullet(Game* game, World* world);
	~PlayerBullet();

	static PlayerBullet* Create(
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
typedef PlayerBullet* pPlayerBullet;

#endif // !__CLIENT_PLAYER_BULLET_H__
